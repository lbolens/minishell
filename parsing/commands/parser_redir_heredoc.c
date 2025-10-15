/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:43:28 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:11:19 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	realloc_heredoc_arrays(t_cmd *command, t_heredoc_arrays *arrays)
{
	arrays->new_delims = my_realloc(command->heredoc_delims,
			(command->heredoc_count + 1) * sizeof(char *),
			(command->heredoc_count) * sizeof(char *));
	arrays->new_quotes = my_realloc(command->heredoc_delim_quotes,
			(command->heredoc_count + 1) * sizeof(bool),
			(command->heredoc_count) * sizeof(bool));
	arrays->new_double_quotes = my_realloc(command->heredoc_delim_double_quotes,
			(command->heredoc_count + 1) * sizeof(bool),
			(command->heredoc_count) * sizeof(bool));
	if (!arrays->new_delims || !arrays->new_quotes
		|| !arrays->new_double_quotes)
	{
		if (arrays->new_delims)
			command->heredoc_delims = arrays->new_delims;
		if (arrays->new_quotes)
			command->heredoc_delim_quotes = arrays->new_quotes;
		if (arrays->new_double_quotes)
			command->heredoc_delim_double_quotes = arrays->new_double_quotes;
		return (0);
	}
	return (1);
}

static void	assign_heredoc_arrays(t_cmd *command, t_heredoc_arrays *arrays)
{
	command->heredoc_delims = arrays->new_delims;
	command->heredoc_delim_quotes = arrays->new_quotes;
	command->heredoc_delim_double_quotes = arrays->new_double_quotes;
}

static void	set_heredoc_data(t_cmd *command, t_redir_info *info)
{
	int	idx;

	idx = command->heredoc_count;
	command->heredoc_delims[idx] = ft_strdup_pars(info->file);
	command->heredoc_delim_quotes[idx] = info->is_single_quote;
	command->heredoc_delim_double_quotes[idx] = info->is_double_quote;
	command->heredoc_count++;
}

bool	handle_heredoc_redir(t_cmd *command, t_redir_info *info)
{
	t_heredoc_arrays	arrays;

	if (!realloc_heredoc_arrays(command, &arrays))
		return (false);
	assign_heredoc_arrays(command, &arrays);
	set_heredoc_data(command, info);
	return (true);
}
