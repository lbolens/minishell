/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:22:50 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/01 15:31:41 by hlongin          ###   ########.fr       */
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

	if (!setup_redirections(cmd, &in_fd, &out_fd))
		return (1);
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	apply_redirs(in_fd, out_fd);
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

	if (!setup_redirections(cmd, &in_fd, &out_fd))
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		apply_redirs(in_fd, out_fd);
		execute_external_command(cmd, env);
		_exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
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
