/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:08:27 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/13 15:18:31 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

t_cmd	*init_new_command(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		printf("Error: Malloc commands\n");
		return (NULL);
	}
	new->append_mode = false;
	new->args = NULL;
	new->args_single_quotes = NULL;
	new->args_count = 0;
	new->heredoc_delims = NULL;
	new->heredoc_delim_quotes = false;
	new->heredoc_delim_double_quotes = NULL;
	new->heredoc_count = 0;
	new->input_file = NULL;
	new->input_single_quotes = false;
	new->output_file = NULL;
	new->output_single_quotes = false;
	new->all_output_files = NULL;
	new->all_output_append = NULL;
	new->output_count = 0;
	new->next = NULL;
	return (new);
}

bool	is_redirection(t_token *token)
{
	if (token->type == TOKEN_REDIRECT_APPEND
		|| token->type == TOKEN_REDIRECT_HEREDOC
		|| token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT)
		return (true);
	return (false);
}

void	ft_lstadd_back_commands(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

bool	handle_input_redir(t_cmd *command, char *file, bool is_single_quote)
{
	if (command->input_file != NULL)
		free(command->input_file);
	command->input_file = ft_strdup_pars(file);
	command->input_single_quotes = is_single_quote;
	return (true);
}
