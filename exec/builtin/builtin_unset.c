/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:29:45 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/15 14:22:17 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
			ft_printf("unset : unset ne prend que des noms\n");
			return (1);
		}
		else
			unset_env_var(env, cmd->args[i]);
		i++;
	}
	return (0);
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
