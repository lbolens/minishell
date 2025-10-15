/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:30:14 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:12:10 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	handle_operator_token(char *str, int *i, t_token **head)
{
	char	*token;
	t_token	*new_token;

	token = extract_operator(str, i);
	if (!token)
		return ;
	new_token = ft_lstnew_pars(token);
	if (!new_token)
	{
		free(token);
		return ;
	}
	ft_lstadd_back_pars(head, new_token);
}

static void	handle_word_token(char *str, int *i, t_token **head)
{
	char	*token;
	t_token	*new_token;
	bool	is_single;
	bool	is_double;

	is_single = false;
	is_double = false;
	token = extract_word(str, i, &is_single, &is_double);
	if (!token)
		return ;
	new_token = ft_lstnew_pars(token);
	if (!new_token)
	{
		free(token);
		return ;
	}
	new_token->single_quotes = is_single;
	new_token->double_quotes = is_double;
	ft_lstadd_back_pars(head, new_token);
}

static void	process_token(char *str, int *i, t_token **head)
{
	if (is_operator(str[*i]))
		handle_operator_token(str, i, head);
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
