/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:28:05 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/09 11:06:04 by lbolens          ###   ########.fr       */
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

static int	process_single_export(char *arg, t_env *env)
{
	char	*var;
	char	*value;
	char	*cleaned_arg;

	cleaned_arg = remove_quotes(arg);
	if (!cleaned_arg || !parse_export(cleaned_arg))
	{
		printf("Error: variable error\n");
		free(cleaned_arg);
		return (1);
	}
	var = extract_var(cleaned_arg);
	value = extract_value(cleaned_arg);
	if (value != NULL)
		set_env_var(env, var, value);
	else
		set_env_var(env, var, "");
	free(var);
	if (value)
		free(value);
	free(cleaned_arg);
	return (0);
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
