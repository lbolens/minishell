/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:54:51 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/13 15:19:31 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static int	realloc_output_arrays(t_cmd *command)
{
	command->all_output_files = realloc(command->all_output_files,
			(command->output_count + 1) * sizeof(char *));
	command->all_output_append = realloc(command->all_output_append,
			(command->output_count + 1) * sizeof(bool));
	if (!command->all_output_files || !command->all_output_append)
		return (0);
	return (1);
}

static void	set_output_data(t_cmd *command, t_types_tokens type, char *file,
		bool is_single_quote)
{
	command->all_output_files[command->output_count] = ft_strdup_pars(file);
	if (type == TOKEN_REDIRECT_APPEND)
		command->all_output_append[command->output_count] = true;
	else
		command->all_output_append[command->output_count] = false;
	command->output_count++;
	if (command->output_file != NULL)
		free(command->output_file);
	command->output_file = ft_strdup_pars(file);
	command->output_single_quotes = is_single_quote;
	command->append_mode = (type == TOKEN_REDIRECT_APPEND);
}

static bool	handle_output_redir(t_cmd *command, t_types_tokens type, char *file,
		bool is_single_quote)
{
	if (!realloc_output_arrays(command))
		return (false);
	set_output_data(command, type, file, is_single_quote);
	return (true);
}

static bool	handle_heredoc_redir(t_cmd *command, char *file,
		bool is_single_quote, bool is_double_quote)
{
	command->heredoc_delims = realloc(command->heredoc_delims,
			(command->heredoc_count + 1) * sizeof(char *));
	command->heredoc_delim_quotes = realloc(command->heredoc_delim_quotes,
			(command->heredoc_count + 1) * sizeof(bool));
	command->heredoc_delim_double_quotes = realloc(command->heredoc_delim_double_quotes,
			(command->heredoc_count + 1) * sizeof(bool));
	if (!command->heredoc_delims || !command->heredoc_delim_quotes
		|| !command->heredoc_delim_double_quotes)
		return (false);
	command->heredoc_delims[command->heredoc_count] = ft_strdup_pars(file);
	command->heredoc_delim_quotes[command->heredoc_count] = is_single_quote;
	command->heredoc_delim_double_quotes[command->heredoc_count] = is_double_quote;
	command->heredoc_count++;
	return (true);
}

bool	redirection(t_cmd *command, t_types_tokens type, char *file,
		bool is_single_quote, bool is_double_quote)
{
	if (type == TOKEN_REDIRECT_IN)
		return (handle_input_redir(command, file, is_single_quote));
	else if (type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_APPEND)
		return (handle_output_redir(command, type, file, is_single_quote));
	else if (type == TOKEN_REDIRECT_HEREDOC)
		return (handle_heredoc_redir(command, file, is_single_quote,
				is_double_quote));
	return (true);
}
