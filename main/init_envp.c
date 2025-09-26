/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:26:02 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/26 14:58:27 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

t_env *init_env(char **envp)
{
    t_env *env;
    int count;
    int i;
    
    env = (t_env *)malloc(sizeof(t_env));
    if (!env)
        return (NULL);
    count = 0;
    while (envp[count])
        count++;
    env->envp = (char**)malloc(sizeof(char*) * (count + 1));
    if (!env->envp)
        return (NULL);
    i = 0;
    while (envp[i])
    {
        env->envp[i] = ft_strdup(envp[i]);
        i++;
    }
    env->envp[i] = NULL;
    env->exit_status = 0;
    return (env);
}
