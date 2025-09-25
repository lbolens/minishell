/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:28:52 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/25 11:27:55 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

bool	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

bool	is_quote(char c)
{
	if (c == 39 || c == '"')
		return (true);
	else
		return (false);
}

char	*extract_operator(char *str, int *i)
{
	char	*operator;

	operator = NULL;
	if ((str[*i] == '>' && str[(*i) + 1] == '>') || (str[*i] == '<' && str[(*i)
			+ 1] == '<'))
	{
		operator = malloc(3 * sizeof(char));
		if (!operator)
			return (NULL);
		operator[0] = str[*i];
		operator[1] = str[(*i) + 1];
		operator[2] = '\0';
		(*i) = (*i) + 2;
	}
	else if (str[*i] == '|' || (str[*i] == '>' && str[(*i) + 1] != '>')
		|| (str[*i] == '<' && str[(*i) + 1] != '<'))
	{
		operator= malloc(2 * sizeof(char));
		if (!operator)
			return (NULL);
		operator[0] = str[*i];
		operator[1] = '\0';
		(*i)++;
	}
	return (operator);
}

char	*extract_word(char *str, int *i)
{
	char	*word;
	int		j;

	j = (*i);
	while (str[j] != ' ' && str[j] != '\t' && str[j] != '<' && str[j] != '>'
		&& str[j] != '|' && str[j] != '\0')
		j++;
	word = malloc((j - (*i) + 1) * sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '<' && str[*i] != '>'
		&& str[*i] != '|' && str[*i] != '\0')
	{
		word[j] = str[*i];
		j++;
		(*i)++;
	}
	word[j] = '\0';
	return (word);
}

char	*extract_quote(char *str, int *i)
{
	char	*in_quote;
	int		j;
	int		size;

	size = get_size_quote(str, *i);
	in_quote = malloc((size + 1) * sizeof(char));
	if (!in_quote)
		return (NULL);
	(*i)++;
	j = 0;
	if (str[(*i) - 1] == '"')
	{
		while (str[*i] != '"' && str[*i] != '\0')
		{
			in_quote[j] = str[*i];
			j++;
			(*i)++;
		}
	}
	else if (str[(*i) - 1] == 39)
	{
		while (str[*i] != 39 && str[*i] != '\0')
		{
			in_quote[j] = str[*i];
			j++;
			(*i)++;
		}
	}
	if (str[*i] != '\0')
		(*i)++;
	in_quote[j] = '\0';
	return (in_quote);
}
