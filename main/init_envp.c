/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:26:02 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/10 10:12:34 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env_list = NULL;
	env->envp = NULL;
	env->exit_status = 0;
	i = 0;
	while (envp[i])
	{
		add_env_var(&env->env_list, envp[i]);
		i++;
	}
	env->envp = env_list_to_array(env->env_list);
	return (env);
}
