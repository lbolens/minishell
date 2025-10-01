/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:17:24 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/01 23:57:34 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

int	execute_cmd_pipeline(t_cmd *cmd_list, t_env *env)
{
	t_cmd *only;

	if (!cmd_list)
		return (0);
	only = cmd_list;
	if (!only->next && only->args && only->args[0] && is_builtin(only->args[0]))
		return (run_builtin_parent(only, env));
	return (execute_pipeline(cmd_list, env));
} 