/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:28:05 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/02 10:00:13 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
		{
			quote = str[i];
			i++; // Saute le guillemet ouvrant
			while (str[i] && str[i] != quote)
			{
				result[j++] = str[i++];
			}
			if (str[i] == quote)
				i++; // Saute le guillemet fermant
		}
		else
		{
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';
	return (result);
}

int	builtin_export(t_cmd *cmd, t_env *env)
{
	if (!cmd->args[1])
		return (export_display_all(env));
	return (export_process_args(cmd, env));
}

int	export_display_all(t_env *env)
{
	t_env_var	*current;

	current = env->env_list;
	while (current)
	{
		if (current->value && current->value[0] != '\0')
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
	return (0);
}

int export_process_args(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*var;
	char	*value;
	char	*cleaned_arg;

	i = 1;
	while (cmd->args[i])
	{
		cleaned_arg = remove_quotes(cmd->args[i]);
		if (!cleaned_arg)
			return (1);
		if (!parse_export(cleaned_arg))
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
		i++;
	}
	return (0);
}
