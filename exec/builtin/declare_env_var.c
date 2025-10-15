/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:43:11 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 14:50:12 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	var_already_declared(t_env_var *list, char *name)
{
	t_env_var	*current;

	current = list;
	while (current)
	{
		if (ft_strcmp_pars(current->name, name) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

static t_env_var	*create_declared_var(char *name)
{
	t_env_var	*new_node;

	new_node = malloc(sizeof(t_env_var));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup_pars(name);
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	add_to_env_list(t_env_var **list, t_env_var *new_node)
{
	t_env_var	*current;

	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	declare_env_var(t_env *env, char *name)
{
	t_env_var	*new_node;

	if (!env || !name)
		return ;
	if (var_already_declared(env->env_list, name))
		return ;
	new_node = create_declared_var(name);
	if (!new_node)
		return ;
	add_to_env_list(&env->env_list, new_node);
}
