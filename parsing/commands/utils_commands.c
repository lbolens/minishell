/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:08:27 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/25 11:28:45 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

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
	new->heredoc_delim = NULL;
	new->input_file = NULL;
	new->next = NULL;
	new->output_file = NULL;
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
