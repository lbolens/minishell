/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:27:13 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:10:33 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	open_final_output(t_cmd *cmd, int i, int *out_fd)
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
	return (1);
}

static int	open_intermediate_output(t_cmd *cmd, int i)
{
	int	tmp_fd;

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
	return (1);
}

static int	process_output_file(t_cmd *cmd, int i, int *out_fd)
{
	if (i == cmd->output_count - 1)
		return (open_final_output(cmd, i, out_fd));
	else
		return (open_intermediate_output(cmd, i));
}

int	setup_output_redir(t_cmd *cmd, int *out_fd)
{
	int	i;

	if (cmd->output_count == 0)
		return (1);
	i = 0;
	while (i < cmd->output_count)
	{
		if (!process_output_file(cmd, i, out_fd))
			return (0);
		i++;
	}
	return (1);
}
