/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_extract.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:33:49 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/14 16:39:12 by lbolens          ###   ########.fr       */
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
	while (str[*i] != ' ' && str[*i] != '\t' && str[*i] != '<'
		&& str[*i] != '>' && str[*i] != '|' && str[*i] != '\0')
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

static int	has_outer_quotes(char *str, int start, t_quote_flags *flags)
{
	int	len;

	len = flags->len;
	if (len < 2)
		return (0);
	if (str[start] == '"' && str[start + len - 1] == '"')
	{
		flags->is_double = true;
		return (1);
	}
	if (str[start] == 39 && str[start + len - 1] == 39)
	{
		flags->is_single = true;
		return (1);
	}
	return (0);
}

char	*extract_word(char *str, int *i, bool *is_single, bool *is_double)
{
	t_extract_data	data;

	data.start = *i;
	*is_single = false;
	*is_double = false;
	data.len = calculate_word_length(str, i);
	data.flags.len = data.len;
	data.flags.is_single = false;
	data.flags.is_double = false;
	has_outer_quotes(str, data.start, &data.flags);
	*is_single = data.flags.is_single;
	*is_double = data.flags.is_double;
	data.word = malloc((data.len + 1) * sizeof(char));
	if (!data.word)
		return (NULL);
	data.j = 0;
	while (data.j < data.len)
	{
		data.word[data.j] = str[data.start + data.j];
		data.j++;
	}
	data.word[data.j] = '\0';
	return (data.word);
}
