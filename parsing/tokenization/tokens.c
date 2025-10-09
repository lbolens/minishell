/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:30:14 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 15:46:29 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static void	handle_operator_token(char *str, int *i, t_token **head)
{
	char	*token;
	t_token	*new_token;

	token = extract_operator(str, i);
	new_token = ft_lstnew_pars(token);
	ft_lstadd_back_pars(head, new_token);
}

/*static void	handle_quote_token(char *str, int *i, t_token **head)
{
	char	*token;
	t_token	*new_token;
	bool	is_single;

	token = extract_quote(str, i, &is_single);
	new_token = ft_lstnew_pars(token);
	new_token->single_quotes = is_single;
	ft_lstadd_back_pars(head, new_token);
}*/

static void	handle_word_token(char *str, int *i, t_token **head)
{
	char	*token;
	t_token	*new_token;

	token = extract_word(str, i);
	new_token = ft_lstnew_pars(token);
	ft_lstadd_back_pars(head, new_token);
}

static void	process_token(char *str, int *i, t_token **head)
{
	if (is_operator(str[*i]))
		handle_operator_token(str, i, head);
	//else if (is_quote(str[*i]))
		//handle_quote_token(str, i, head);
	else
		handle_word_token(str, i, head);
}

t_token	*tokenization(char *str)
{
	t_token	*head;
	t_token	*eof_token;
	int		i;

	head = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			process_token(str, &i, &head);
	}
	eof_token = ft_lstnew_pars(NULL);
	ft_lstadd_back_pars(&head, eof_token);
	return (head);
}
