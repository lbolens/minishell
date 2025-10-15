/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:03:47 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 14:50:42 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
		if (current->value == NULL)
			ft_printf("export %s\n", current->name);
		else if (current->value[0] == '\0')
			ft_printf("export %s=\"\"\n", current->name);
		else
			ft_printf("export %s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}

static int	check_overflow(char *str)
{
	int			i;
	long long	result;

	i = 0;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (result > (9223372036854775807LL - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (check_overflow(str));
}
