/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:26:02 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/15 11:10:47 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	increment_shlvl(t_env *env)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl;

	shlvl_str = get_env_value(env, "SHLVL");
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	new_shlvl = ft_itoa_pars(shlvl);
	if (new_shlvl)
	{
		set_env_var(env, "SHLVL", new_shlvl);
		free(new_shlvl);
	}
}

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
	env->current_tokens = NULL;
	env->current_cmd = NULL;
	env->current_input = NULL;
	env->pipeline_pids = NULL;
	i = 0;
	while (envp[i])
	{
		add_env_var(&env->env_list, envp[i]);
		i++;
	}
	increment_shlvl(env);
	env->envp = env_list_to_array(env->env_list);
	return (env);
}
