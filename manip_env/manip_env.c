/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:21:37 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 11:37:27 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

t_env_var	*create_new_env_var(char *str)
{
	t_env_var	*node;

	node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!node)
		return (NULL);
	node->name = extract_name(str);
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	node->value = extract_env_value(str);
	if (!node->value)
	{
		free(node->name);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

char	*get_env_value(t_env *env, char *name)
{
	t_env_var	*current;

	if (!env || !name)
		return (NULL);
	current = env->env_list;
	while (current)
	{
		if (ft_strcmp_pars(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static int	update_existing_var(t_env_var *list, char *name, char *value)
{
	t_env_var	*current;
	char		*new_value;

	current = list;
	while (current)
	{
		if (ft_strcmp_pars(current->name, name) == 0)
		{
			new_value = ft_strdup_pars(value);
			if (!new_value)
				return (0);
			free(current->value);
			current->value = new_value;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	set_env_var(t_env *env, char *name, char *value)
{
	char	*env_string;
	int		total_len;

	if (!env || !name || !value)
		return ;
	if (update_existing_var(env->env_list, name, value))
		return ;
	total_len = ft_strlen_pars(name) + ft_strlen_pars(value) + 2;
	env_string = malloc(total_len);
	if (!env_string)
		return ;
	ft_strlcpy_pars(env_string, name, ft_strlen_pars(name) + 1);
	ft_strlcat(env_string, "=", ft_strlen_pars(name) + 2);
	ft_strlcat(env_string, value, total_len);
	add_env_var(&env->env_list, env_string);
	free(env_string);
}

void	unset_env_var(t_env *env, char *name)
{
	t_env_var	*current;
	t_env_var	*prev;

	if (!env || !name || !env->env_list)
		return ;
	current = env->env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp_pars(current->name, name) == 0)
		{
			if (prev == NULL)
				env->env_list = current->next;
			else
				prev->next = current->next;
			ft_lstdelone_pars(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
