/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:28:52 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/03 12:41:56 by lbolens          ###   ########.fr       */
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
		operator = malloc(2 * sizeof(char));
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
	int		start;
	int		len;
	char	*word;
	int		j;

	start = *i;
	
	// Calcule la longueur en incluant les quotes
	while (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '<' 
		&& str[*i] != '>' && str[*i] != '|' && str[*i] != '\0')
	{
		if (str[*i] == '"')
		{
			(*i)++;
			while (str[*i] != '"' && str[*i] != '\0')
				(*i)++;
			if (str[*i] == '"')
				(*i)++;
		}
		else if (str[*i] == 39)
		{
			(*i)++;
			while (str[*i] != 39 && str[*i] != '\0')
				(*i)++;
			if (str[*i] == 39)
				(*i)++;
		}
		else
			(*i)++;
	}
	
	len = *i - start;
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	
	j = 0;
	while (j < len)
	{
		word[j] = str[start + j];
		j++;
	}
	word[j] = '\0';
	
	return (word);
}

char	*extract_quote(char *str, int *i, bool *is_single_quote)
{
	char	*in_quote;
	int		j;
	int		size;
	char quote_type;
	
	quote_type = str[*i];
	*is_single_quote = (quote_type == 39 || quote_type == '"');
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
