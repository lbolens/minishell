/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:06:38 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/23 19:18:27 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_cmd *cmd, t_exec_env *env)
{
	if (!cmd->args[1])
		exit(env->exit_status);
	else if (is_valid_number(cmd->args[1]))
		exit(atoi(cmd->args[1]));
	else
	{
		printf("exit: numeric argument required\n");
		exit(2);
	}
}

int	builtin_pwd(t_cmd *cmd, t_exec_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	builtin_env(t_cmd *cmd, t_exec_env *exec_env)
{
	int	i;

	i = 0;
	while (exec_env->envp[i])
	{
		printf("%s\n", exec_env->envp[i]);
		i++;
	}
	return (0);
}

int	builtin_echo(t_cmd *cmd, t_exec_env *env)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
