/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:00:03 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/03 13:02:06 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

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

int	setup_redirections(t_cmd *cmd, t_env *env, int *in_fd, int *out_fd)
{
	int	i;
	int	tmp_fd;

	*in_fd = STDIN_FILENO;
	*out_fd = STDOUT_FILENO;
	if (cmd->heredoc_delims)
	{
		*in_fd = process_heredoc(cmd, env);
		if (*in_fd == -1)
			return (0);
		if (*in_fd == -2)
			return (0);
	}
	else if (cmd->input_file && !open_in(cmd->input_file, in_fd))
		return (0);
	if (cmd->output_count > 0)
	{
		i = 0;
		while (i < cmd->output_count)
		{
			if (i == cmd->output_count - 1)
			{
				if (cmd->all_output_append[i])
				{
					if (!open_out_append(cmd->all_output_files[i], out_fd))
						return (0);
				}
				else
				{
					if (!open_out_trunc(cmd->all_output_files[i], out_fd))
						return (0);
				}
			}
			else
			{
				if (cmd->all_output_append[i])
				{
					if (!open_out_append(cmd->all_output_files[i], &tmp_fd))
						return (0);
				}
				else
				{
					if (!open_out_trunc(cmd->all_output_files[i], &tmp_fd))
						return (0);
				}
				close(tmp_fd);
			}
			i++;
		}
	}
	return (1);
}
