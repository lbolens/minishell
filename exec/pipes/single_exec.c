/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:22:50 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/10 10:22:27 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

void	apply_redirs(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void	restore_stdio(int saved_in, int saved_out)
{
	if (saved_in != -1)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

int	run_builtin_parent(t_cmd *cmd, t_env *env)
{
	int	in_fd;
	int	out_fd;
	int	saved_in;
	int	saved_out;
	int	ret;

	if (!setup_redirections(cmd, env, &in_fd, &out_fd))
		return (1);
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	apply_redirs(in_fd, out_fd);
	if (ft_strcmp_pars(cmd->args[0], "exit") == 0)
	{
		printf("exit\n");
		ret = execute_builtin(cmd, env);
		restore_stdio(saved_in, saved_out);
		exit(ret);
	}
	ret = execute_builtin(cmd, env);
	restore_stdio(saved_in, saved_out);
	return (ret);
}

int	run_external_child(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	int		in_fd;
	int		out_fd;
	char	*path;
	char	**env_array;

	if (!setup_redirections(cmd, env, &in_fd, &out_fd))
		return (1);
	path = find_command_path(cmd->args[0], env->envp);
	if (!path)
	{
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		fprintf(stderr, "%s: command not found\n", cmd->args[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		free(path);
		return (1);
	}
	if (pid == 0)
	{
		restore_signal();
		apply_redirs(in_fd, out_fd);
		env_array = env_list_to_array(env->env_list);
		execve(path, cmd->args, env_array);
		perror(path);
		free_tab(env_array);
		free(path);
		_exit(126);
	}
	free(path);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_single_cmd(t_cmd *cmd, t_env *env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]))
		return (run_builtin_parent(cmd, env));
	return (run_external_child(cmd, env));
}
