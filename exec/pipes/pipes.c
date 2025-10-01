/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:12:24 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/02 00:05:50 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

void	close_if_valid(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	child_exec(t_cmd *cmd, t_env *env, int in_fd, int out_fd)
{
	char	**envp;
	char	*path;

	restore_signal();
	apply_redirs(in_fd, out_fd);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
		_exit(execute_builtin(cmd, env));
	envp = env_list_to_array(env->env_list);
	path = find_command_path(cmd->args[0], envp);
	if (!path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		free_tab(envp);
		_exit(127); // attention fonction interdites
	}
	execve(path, cmd->args, envp);
	perror(path);
	free(path);
	free_tab(envp);
	_exit(126);
}

int	spawn(t_cmd *cmd, t_env *env, int last_in, int *next_in)
{
	int		in_fd;
	int		out_fd;
	int		p[2];
	pid_t	pid;
	int		has_next;

	has_next = (cmd->next != NULL);
	if (has_next && pipe(p) == -1)
		return (-1);
	if (!setup_redirections(cmd, &in_fd, &out_fd))
		return (has_next ? (close(p[0]), close(p[1]), -1) : -1);
	if (in_fd == STDIN_FILENO && last_in >= 0)
		in_fd = last_in;
	if (out_fd == STDOUT_FILENO && has_next)
		out_fd = p[1];
	pid = fork();
	if (pid == -1)
		return (has_next ? (close(p[0]), close(p[1]), -1) : -1);
	if (pid == 0)
	{
		if (has_next)
			close(p[0]);
		child_exec(cmd, env, in_fd, out_fd);
	}
	if (in_fd != STDIN_FILENO && in_fd != last_in)
		close_if_valid(in_fd);
	if (out_fd != STDOUT_FILENO && out_fd != p[1])
		close_if_valid(out_fd);
	if (last_in >= 0)
		close_if_valid(last_in);
	*next_in = has_next ? p[0] : -1;
	if (has_next)
		close(p[1]);
	return (pid);
}

int	wait_all(pid_t *pids, int n)
{
	int	i;
	int	wst;
	int	status;

	i = 0;
	status = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &wst, 0) > 0 && i == n - 1)
		{
			if (WIFEXITED(wst))
				status = WEXITSTATUS(wst);
			else if (WIFSIGNALED(wst))
				status = 128 + WTERMSIG(wst);
		}
		i++;
	}
	return (status);
}

int	execute_pipeline(t_cmd *cmd_list, t_env *env)
{
	int		count;
	int		i;
	int		last_in;
	int		next_in;
	t_cmd	*cur;
	pid_t	*pids;

	if (!cmd_list || !cmd_list->next)
		return (execute_single_cmd(cmd_list, env));
	count = 0;
	cur = cmd_list;
	while (cur && ++count)
		cur = cur->next;
	pids = (pid_t *)malloc(sizeof(pid_t) * count);
	if (!pids)
		return (1);
	i = 0;
	last_in = -1;
	cur = cmd_list;
	while (cur)
	{
		pids[i] = spawn(cur, env, last_in, &next_in);
		if (pids[i] == -1)
			return (free(pids), 1);
		last_in = next_in;
		cur = cur->next;
		i++;
	}
	i = wait_all(pids, count);
	free(pids);
	return (i);
}
