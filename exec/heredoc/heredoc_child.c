/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:57:49 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:10:04 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static bool	has_any_quotes(t_cmd *cmd, int i)
{
	if (cmd->heredoc_delim_quotes[i])
		return (true);
	if (cmd->heredoc_delim_double_quotes[i])
		return (true);
	return (false);
}

static void	heredoc_child_process(int pipe_fd[2], t_cmd *cmd, int i, t_env *env)
{
	bool	quotes;
	int		status;

	setup_heredoc_signals(env);
	quotes = has_any_quotes(cmd, i);
	status = read_one_heredoc(pipe_fd, cmd->heredoc_delims[i], quotes, env);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	cleanup_env(env);
	if (status == HEREDOC_INTERRUPTED)
		exit(130);
	exit(0);
}

static int	fork_heredoc_child(int pipe_fd[2], t_cmd *cmd, int i, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
		heredoc_child_process(pipe_fd, cmd, i, env);
	return (pid);
}

int	handle_heredoc_child(int pipe_fd[2], t_cmd *cmd, int i, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork_heredoc_child(pipe_fd, cmd, i, env);
	if (pid == -1)
		return (-1);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	return (check_heredoc_status(status, pipe_fd[0], env));
}
