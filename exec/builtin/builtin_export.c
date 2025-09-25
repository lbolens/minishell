/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:28:05 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 11:11:46 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	builtin_export(t_cmd *cmd, t_env *env)
{
	if (!cmd->args[1])
		return (export_display_all(env));
	return (export_process_args(cmd, env));
}

int	export_display_all(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		printf("declare -x %s\n", env->envp[i]);
		i++;
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
			update_env_variable(env, var, value);
		else
			printf("export: %s: variable not found\n", var);
		free(var);
		if (value)
			free(value);
		i++;
	}
	return (0);
}
