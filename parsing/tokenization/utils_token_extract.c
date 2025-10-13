/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_extract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:33:49 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/13 15:31:57 by lbolens          ###   ########.fr       */
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

static int	has_outer_quotes(char *str, int start, int len, bool *is_single,
		bool *is_double)
{
	if (len < 2)
		return (0);
	if (str[start] == '"' && str[start + len - 1] == '"')
	{
		*is_double = true;
		return (1);
	}
	if (str[start] == 39 && str[start + len - 1] == 39)
	{
		*is_single = true;
		return (1);
	}
	return (0);
}

char	*extract_word(char *str, int *i, bool *is_single, bool *is_double)
{
	int		start;
	int		len;
	char	*word;
	int		j;

	start = *i;
	*is_single = false;
	*is_double = false;
	len = calculate_word_length(str, i);
	has_outer_quotes(str, start, len, is_single, is_double);
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

/*static void	extract_content(char *str, int *i, char *in_quote, char quote)
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
}*/
