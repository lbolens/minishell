/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:21:35 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/13 15:25:59 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

static void	write_heredoc_line(int pipe_fd, char *line, bool has_quotes,
		t_env *env)
{
	char	*expanded;

	if (!has_quotes)
		expanded = build_full_command(line, env, 0, true);
	else
		expanded = line;
	write(pipe_fd, expanded, ft_strlen_pars(expanded));
	write(pipe_fd, "\n", 1);
	if (expanded != line)
		free(expanded);
}

void	read_one_heredoc(int pipe_fd[2], char *delim, bool has_quotes,
		t_env *env)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("warning: here-document delimited by end-of-file wanted\n");
			break ;
		}
		if (ft_strcmp_pars(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(pipe_fd[1], line, has_quotes, env);
		free(line);
	}
}

static int	check_heredoc_status(int status, int pipe_fd, t_env *env)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(pipe_fd);
		env->exit_status = 130;
		return (-2);
	}
	return (0);
}

static int	handle_heredoc_child(int pipe_fd[2], t_cmd *cmd, int i, t_env *env)
{
	pid_t	pid;
	int		status;
	bool	has_any_quotes;

	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		setup_heredoc_signals();
		has_any_quotes = cmd->heredoc_delim_quotes[i]
			|| cmd->heredoc_delim_double_quotes[i];
		read_one_heredoc(pipe_fd, cmd->heredoc_delims[i], has_any_quotes, env);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	return (check_heredoc_status(status, pipe_fd[0], env));
}

int	process_heredoc(t_cmd *cmd, t_env *env)
{
	int	pipe_fd[2];
	int	final_fd;
	int	i;
	int	result;

	if (cmd->heredoc_count == 0)
		return (STDIN_FILENO);
	i = 0;
	while (i < cmd->heredoc_count)
	{
		if (pipe(pipe_fd) == -1)
			return (-1);
		result = handle_heredoc_child(pipe_fd, cmd, i, env);
		if (result != 0)
			return (result);
		if (i == cmd->heredoc_count - 1)
			final_fd = pipe_fd[0];
		else
			close(pipe_fd[0]);
		i++;
	}
	return (final_fd);
}
