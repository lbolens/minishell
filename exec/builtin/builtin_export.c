/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:28:05 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/02 00:20:46 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

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

int	export_process_args(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*var;
	char	*value;

	i = 1;
	while (cmd->args[i])
	{
		if (!parse_export(cmd->args[i]))
		{
			printf("erreur de variable\n");
			return (1);
		}
		var = extract_var(cmd->args[i]);
		value = extract_value(cmd->args[i]);
		if (value != NULL)
			set_env_var(env, var, value);
		else
			set_env_var(env, var, "");
		free(var);
		if (value)
			free(value);
		i++;
	}
	return (0);
}
