/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:06:38 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 11:29:16 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

int     builtin_exit(t_cmd *cmd,t_env *env)
{
    int     exit_code;
    
    if(!cmd->args[1])
        exit_code = env->exit_status;
    else if (is_valid_number(cmd->args[1]))
        exit_code = ft_atoi(cmd->args[1]);
    else
    {
        printf("exit : %s: numeric argument required\n", cmd->args[1]);
        exit_code = 2;
    }
    printf("exit\n");
    exit(exit_code);
    return (0);
}

int	builtin_pwd(t_cmd *cmd, t_env *env)
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

int	builtin_env(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		printf("%s\n", env->envp[i]);
		i++;
	}
	return (0);
}

int	builtin_echo(t_cmd *cmd, t_env *env)
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
