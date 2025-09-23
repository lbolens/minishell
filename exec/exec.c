/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:06:38 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/23 16:10:05 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		builtin_pwd(t_cmd *cmd, t_exec_env)
{
	
}

int		builtin_env(t_cmd *cmd, t_exec_env *exec_env)
{
	int		i;

	i = 0;
	while (exec_env->envp[i])
	{
		printf("%s\n", exec_env->envp[i]);
		i++;
	}
	return (0);
}

t_exec_env	*init_exec_env(char **envp)
{
	t_exec_env *env;

	env = malloc(sizeof(t_exec_env));
	env->envp = envp;
	env->exit_status = 0;
	return (env);
}