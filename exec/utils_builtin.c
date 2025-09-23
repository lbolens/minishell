/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:55:58 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/23 18:03:08 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	return (false);
}

int	execute_builtin(t_cmd *cmd, t_exec_env *env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd(cmd, env));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(cmd, env));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd, env));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd, env));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		builtin_exit(cmd, env);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd, env));
	return (1);
}

t_exec_env	*init_exec_env(char **envp)
{
	t_exec_env	*env;

	env = malloc(sizeof(t_exec_env));
	if (!env)
		return (NULL);
	env->envp = envp;
	env->exit_status = 0;
	return (env);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}
