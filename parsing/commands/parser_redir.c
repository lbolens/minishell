/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:54:51 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:11:23 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	realloc_output_arrays(t_cmd *command)
{
	char	**new_files;
	bool	*new_append;

	new_files = my_realloc(command->all_output_files, (command->output_count
				+ 1) * sizeof(char *), (command->output_count)
			* sizeof(char *));
	new_append = my_realloc(command->all_output_append, (command->output_count
				+ 1) * sizeof(bool), (command->output_count) * sizeof(bool));
	if (!new_files || !new_append)
	{
		if (new_files)
			command->all_output_files = new_files;
		if (new_append)
			command->all_output_append = new_append;
		return (0);
	}
	command->all_output_files = new_files;
	command->all_output_append = new_append;
	return (1);
}

static void	set_output_data(t_cmd *command, t_redir_info *info)
{
	int	idx;

	idx = command->output_count;
	command->all_output_files[idx] = ft_strdup_pars(info->file);
	if (info->type == TOKEN_REDIRECT_APPEND)
		command->all_output_append[command->output_count] = true;
	else
		command->all_output_append[command->output_count] = false;
	command->output_count++;
	if (command->output_file != NULL)
		free(command->output_file);
	command->output_file = ft_strdup_pars(info->file);
	command->output_single_quotes = info->is_single_quote;
	command->append_mode = (info->type == TOKEN_REDIRECT_APPEND);
}

static bool	handle_output_redir(t_cmd *command, t_redir_info *info)
{
	if (!realloc_output_arrays(command))
		return (false);
	set_output_data(command, info);
	return (true);
}

bool	redirection(t_cmd *command, t_redir_info *info)
{
	if (info->type == TOKEN_REDIRECT_IN)
		return (handle_input_redir(command, info->file, info->is_single_quote));
	else if (info->type == TOKEN_REDIRECT_OUT
		|| info->type == TOKEN_REDIRECT_APPEND)
		return (handle_output_redir(command, info));
	else if (info->type == TOKEN_REDIRECT_HEREDOC)
		return (handle_heredoc_redir(command, info));
	return (true);
}
