/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:20:03 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/01 16:17:05 by hlongin          ###   ########.fr       */
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

int	setup_redirections(t_cmd *cmd, int *in_fd, int *out_fd)
{
	*in_fd = STDIN_FILENO;
	*out_fd = STDOUT_FILENO;
	if (cmd->input_file && !open_in(cmd->input_file, in_fd))
		return (0);
	if (cmd->output_file)
	{
		if (cmd->append_mode)
		{
			if (!open_out_append(cmd->output_file, out_fd))
				return (0);
		}
		else
		{
			if (!open_out_trunc(cmd->output_file, out_fd))
				return (0);
		}
	}
	return (1);
}
