/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:55:58 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 14:21:45 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

bool	is_builtin(char *cmd_name)
{
	if (ft_strncmp(cmd_name, "pwd", 4) == 0 && ft_strlen(cmd_name) == 3)
		return (true);
	if (ft_strncmp(cmd_name, "echo", 5) == 0 && ft_strlen(cmd_name) == 4)
		return (true);
	if (ft_strncmp(cmd_name, "env", 4) == 0 && ft_strlen(cmd_name) == 3)
		return (true);
	if (ft_strncmp(cmd_name, "cd", 3) == 0 && ft_strlen(cmd_name) == 2)
		return (true);
	if (ft_strncmp(cmd_name, "export", 7) == 0 && ft_strlen(cmd_name) == 6)
		return (true);
	if (ft_strncmp(cmd_name, "exit", 5) == 0 && ft_strlen(cmd_name) == 4)
		return (true);
	if (ft_strncmp(cmd_name, "unset", 6) == 0 && ft_strlen(cmd_name) == 5)
		return (true);
	return (false);
}

int	execute_builtin(t_cmd *cmd, t_env *env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0 && ft_strlen(cmd->args[0]) == 3)
		return (builtin_pwd(cmd, env));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0 && ft_strlen(cmd->args[0]) == 3)
		return (builtin_env(cmd, env));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0 && ft_strlen(cmd->args[0]) == 2)
		return (builtin_cd(cmd, env));
	if (ft_strncmp(cmd->args[0], "export", 7) == 0
		&& ft_strlen(cmd->args[0]) == 6)
	{		
		return (builtin_export(cmd, env));
	}
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0
		&& ft_strlen(cmd->args[0]) == 4)
	{	
		builtin_exit(cmd, env);
	}
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0
		&& ft_strlen(cmd->args[0]) == 5)
	{
		return (builtin_unset(cmd, env));
	}
	return (1);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	cd_error(char *msg)
{
	perror(msg);
	return (1);
}
