/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:38:14 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:12:25 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_args(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->args_single_quotes)
		free(cmd->args_single_quotes);
}

void	free_output_files(t_cmd *cmd)
{
	int	i;

	if (cmd->all_output_files)
	{
		i = 0;
		while (i < cmd->output_count)
		{
			free(cmd->all_output_files[i]);
			i++;
		}
		free(cmd->all_output_files);
		free(cmd->all_output_append);
	}
}

void	free_heredoc_delims(t_cmd *cmd)
{
	int	i;

	if (cmd->heredoc_delims)
	{
		i = 0;
		while (i < cmd->heredoc_count)
		{
			free(cmd->heredoc_delims[i]);
			i++;
		}
		free(cmd->heredoc_delims);
		free(cmd->heredoc_delim_quotes);
		free(cmd->heredoc_delim_double_quotes);
	}
}

void	free_single_command(t_cmd *cmd)
{
	free_args(cmd);
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	free_output_files(cmd);
	free_heredoc_delims(cmd);
	free(cmd);
}
