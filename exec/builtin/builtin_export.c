/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:28:05 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/13 15:07:09 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static int	copy_quoted_content(char *str, char *result, int *i, int *j)
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

int	builtin_export(t_cmd *cmd, t_env *env)
{
	if (!cmd->args[1])
		return (export_display_all(env));
	return (export_process_args(cmd, env));
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
			copy_quoted_content(str, result, &i, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	export_process_args(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (process_single_export(cmd->args[i], env) != 0)
			return (1);
		i++;
	}
	return (0);
}
