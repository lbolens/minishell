/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:03:47 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 11:06:08 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

int	cd_error(char *msg)
{
	perror(msg);
	return (1);
}

int	export_display_all(t_env *env)
{
	t_env_var	*current;

	current = env->env_list;
	while (current)
	{
		if (current->value && current->value[0] != '\0')
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
	return (0);
}
