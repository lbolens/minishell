/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_extract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:33:49 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 14:34:04 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static void	skip_quoted_section(char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i] != quote && str[*i] != '\0')
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
}

static int	calculate_word_length(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '<' && str[*i] != '>'
		&& str[*i] != '|' && str[*i] != '\0')
	{
		if (str[*i] == '"')
			skip_quoted_section(str, i, '"');
		else if (str[*i] == 39)
			skip_quoted_section(str, i, 39);
		else
			(*i)++;
	}
	return (*i - start);
}

char	*extract_word(char *str, int *i)
{
	int		start;
	int		len;
	char	*word;
	int		j;

	start = *i;
	len = calculate_word_length(str, i);
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

static void	extract_content(char *str, int *i, char *in_quote, char quote)
{
	int	j;

	j = 0;
	while (str[*i] != quote && str[*i] != '\0')
	{
		in_quote[j] = str[*i];
		j++;
		(*i)++;
	}
	in_quote[j] = '\0';
}

char	*extract_quote(char *str, int *i, bool *is_single_quote)
{
	char	*in_quote;
	int		size;
	char	quote_type;

	quote_type = str[*i];
	*is_single_quote = (quote_type == 39);
	size = get_size_quote(str, *i);
	in_quote = malloc((size + 1) * sizeof(char));
	if (!in_quote)
		return (NULL);
	(*i)++;
	if (quote_type == '"')
		extract_content(str, i, in_quote, '"');
	else if (quote_type == 39)
		extract_content(str, i, in_quote, 39);
	if (str[*i] != '\0')
		(*i)++;
	return (in_quote);
}
