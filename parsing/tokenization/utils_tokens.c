/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:28:52 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 15:46:56 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

bool	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

/*bool	is_quote(char c)
{
	if (c == 39 || c == '"')
		return (true);
	else
		return (false);
}*/

static char	*create_double_operator(char *str, int *i)
{
	char	*operator;

	operator = malloc(3 * sizeof(char));
	if (!operator)
		return (NULL);
	operator[0] = str[*i];
	operator[1] = str[(*i) + 1];
	operator[2] = '\0';
	(*i) = (*i) + 2;
	return (operator);
}

static char	*create_single_operator(char *str, int *i)
{
	char	*operator;

	operator = malloc(2 * sizeof(char));
	if (!operator)
		return (NULL);
	operator[0] = str[*i];
	operator[1] = '\0';
	(*i)++;
	return (operator);
}

char	*extract_operator(char *str, int *i)
{
	if ((str[*i] == '>' && str[(*i) + 1] == '>') || (str[*i] == '<' && str[(*i)
				+ 1] == '<'))
		return (create_double_operator(str, i));
	else if (str[*i] == '|' || (str[*i] == '>' && str[(*i) + 1] != '>')
		|| (str[*i] == '<' && str[(*i) + 1] != '<'))
		return (create_single_operator(str, i));
	return (NULL);
}
