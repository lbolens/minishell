/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:00:03 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/15 11:10:36 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	open_in(const char *path, int *fd)
{
	int	f;

	if (!path)
		return (1);
	f = open(path, O_RDONLY);
	if (f < 0)
		return (0);
	*fd = f;
	return (1);
}

int	open_out_trunc(const char *path, int *fd)
{
	int	f;

	f = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (f < 0)
		return (0);
	*fd = f;
	return (1);
}

int	open_out_append(const char *path, int *fd)
{
	int	f;

	f = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (f < 0)
		return (0);
	*fd = f;
	return (1);
}

static int	setup_input_redir(t_cmd *cmd, t_env *env, int *in_fd)
{
	if (cmd->heredoc_delims)
	{
		*in_fd = process_heredoc(cmd, env);
		if (*in_fd == -1 || *in_fd == -2)
			return (0);
	}
	else if (cmd->input_file && !open_in(cmd->input_file, in_fd))
		return (0);
	return (1);
}

int	setup_redirections(t_cmd *cmd, t_env *env, int *in_fd, int *out_fd)
{
	*in_fd = STDIN_FILENO;
	*out_fd = STDOUT_FILENO;
	if (!setup_input_redir(cmd, env, in_fd))
		return (0);
	if (!setup_output_redir(cmd, out_fd))
		return (0);
	return (1);
}
