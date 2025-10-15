/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:35:13 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:12:38 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	copy_quoted_section(char *str, char *result, int *i, int *j)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		result[(*j)++] = str[(*i)++];
	}
	if (str[*i] == quote)
		(*i)++;
	return (0);
}

char	*remove_quotes_from_string(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc((ft_strlen_pars(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
			copy_quoted_section(str, result, &i, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	remove_quotes_from_args(t_cmd *commands)
{
	char	*cleaned;
	int		i;

	i = 0;
	while (commands->args && commands->args[i])
	{
		cleaned = remove_quotes_from_string(commands->args[i]);
		if (cleaned)
		{
			free(commands->args[i]);
			commands->args[i] = cleaned;
		}
		i++;
	}
}

void	remove_quotes_from_input(t_cmd *commands)
{
	char	*cleaned;

	if (commands->input_file)
	{
		cleaned = remove_quotes_from_string(commands->input_file);
		if (cleaned)
		{
			free(commands->input_file);
			commands->input_file = cleaned;
		}
	}
}

void	remove_quotes_from_outputs(t_cmd *commands)
{
	char	*cleaned;
	int		i;

	i = 0;
	while (i < commands->output_count)
	{
		if (commands->all_output_files[i])
		{
			cleaned = remove_quotes_from_string(commands->all_output_files[i]);
			if (cleaned)
			{
				free(commands->all_output_files[i]);
				commands->all_output_files[i] = cleaned;
			}
		}
		i++;
	}
}
