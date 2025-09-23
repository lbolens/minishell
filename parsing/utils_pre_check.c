/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pre_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:39:37 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/23 15:42:42 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_empty(char *str)
{
	if (str[0] == '\0')
		return (true);
	return (false);
}

bool	check_quotes(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote % 2 == 0)
			single_quote++;
		else if (str[i] == '\"' && single_quote % 2 == 0)
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
	{
		printf("Error: Unmatched quotes\n");
		return (true);
	}
	return (false);
}

bool	check_pipes(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (len == 0)
		return (false);
	if (str[0] == '|')
	{
		printf("Error: Pipe at the beginning\n");
		return (true);
	}
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
		{
			printf("Error: Consecutive pipes\n");
			return (true);
		}
		i++;
	}
	if (len > 0 && str[len - 1] == '|')
	{
		printf("Error: Pipe at the end\n");
		return (true);
	}
	return (false);
}

bool	check_forbidden_sequences(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '<') || (str[i] == '<' && str[i
				+ 1] == '>') || (str[i] == ';' && str[i + 1] == ';')
			|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
			|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			|| (str[i] == '>' && str[i + 1] == '|'))
		{
			printf("Error: Forbidden sequence\n");
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_operators(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			j = i + 1;
			if (str[j] == str[i])
				j++;
			while (str[j] == ' ' || str[j] == '\t')
				j++;
			if (str[j] == '\0')
			{
				printf("Error: Redirection without target\n");
				return (true);
			}
			if (str[j] == '|' || str[j] == '<' || str[j] == '>')
			{
				printf("Error: Invalid operator after redirection\n");
				return (true);
			}
		}
		i++;
	}
	return (false);
}
