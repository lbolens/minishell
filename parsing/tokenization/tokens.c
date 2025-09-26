/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:30:14 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/26 13:26:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

t_token	*tokenization(char *str)
{
	t_token	*head;
	t_token	*new_token;
	t_token	*eof_token;
	bool	is_single;
	char	*token;
	int		i;

	head = NULL;
	new_token = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
		{
			if (is_operator(str[i]))
			{
				token = extract_operator(str, &i);
				new_token = ft_lstnew_pars(token);
				ft_lstadd_back_pars(&head, new_token);
			}
			else if (is_quote(str[i]))
			{
				token = extract_quote(str, &i, &is_single);
				new_token = ft_lstnew_pars(token);
				new_token->single_quotes = is_single;
				ft_lstadd_back_pars(&head, new_token);
			}
			else
			{
				token = extract_word(str, &i);
				new_token = ft_lstnew_pars(token);
				ft_lstadd_back_pars(&head, new_token);
			}
		}
	}
	eof_token = ft_lstnew_pars(NULL);
	ft_lstadd_back_pars(&head, eof_token);
	return (head);
}
