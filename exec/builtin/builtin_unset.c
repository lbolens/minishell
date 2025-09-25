/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:29:45 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 11:12:36 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	builtin_unset(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
		return (0);
	while (cmd->args[i])
	{
		if (!parse_unset(cmd->args[i]))
		{
			printf("unset : unset ne prend que des noms\n");
			return (1);
		}
		else
			remove_env_variable(env, cmd->args[i]);
		i++;
	}
	return (1);
}

void	remove_env_variable(t_env *env, char *arg)
{
	char	*var_name;
	int		len_var;
	int		i;

	i = 0;
	var_name = extract_var(arg);
	len_var = ft_strlen(var_name);
	while (env->envp[i])
    {    
        if (ft_strncmp(env->envp[i], var_name, len_var) == 0
		&& env->envp[i][len_var] == '=')
        {
            free(env->envp[i]);
            while (env->envp[i + 1])
            {
                env->envp[i] = env->envp[i + 1];
                i++;
            }
            env->envp[i] = NULL;
            break;
        }
        i++;
	}
    free(var_name);
}

int	parse_unset(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
