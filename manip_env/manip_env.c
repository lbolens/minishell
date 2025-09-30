/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:21:37 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/30 14:47:40 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

t_env_var	*create_new_env_var(char *str)
{
	t_env_var	*node;
	int			i;

	node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!node)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	// Extraire le nom
	node->name = malloc(i + 1);
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	ft_strlcpy_pars(node->name, str, i + 1);
	// Extraire la valeur
	if (str[i] == '=')
		node->value = ft_strdup_pars(str + i + 1);
	else
		node->value = ft_strdup_pars(""); // Si il n y a pas de "="
	node->next = NULL;
	return (node);
}

// Chercher une variable
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

// Mettre a jour une variable (pour export)
void	set_env_var(t_env *env, char *name, char *value)
{
	t_env_var	*current;
	char		*new_value;
	char		*env_string;

	if (!env || !name || !value)
		return ;
	current = env->env_list;
	while (current)
	{
		if (ft_strcmp_pars(current->name, name) == 0)
		{
			new_value = ft_strdup_pars(value);
			if (!new_value)
				return ;
			free(current->value);
			current->value = new_value;
			return ;
		}
		current = current->next;
	}
	env_string = malloc(ft_strlen_pars(name) + ft_strlen_pars(value) + 2);
	if (!env_string)
		return ;
	ft_strlcpy_pars(env_string, name, ft_strlen_pars(name) + 1);
	ft_strlcat(env_string, "=", ft_strlen_pars(name) + 2);
	ft_strlcat(env_string, value, ft_strlen_pars(name) + ft_strlen_pars(value)
		+ 2);
	add_env_var(&env->env_list, env_string);
	free(env_string);
}

// Supprimer une variable (pour unset)
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

// Convertir la liste en char** pour execve
char	**env_list_to_array(t_env_var *list)
{
	t_env_var	*current;
	int			nbr;
	int			len;
	int			i;

	char **to_return ;
	nbr = ft_lstsize_pars(list);
	to_return = (malloc((nbr + 1) * sizeof(char *)));
	if (!to_return)
		return (NULL);
	current = list;
	i = 0;
	while (current)
	{
		len = ft_strlen_pars(current->name) + ft_strlen_pars(current->value)
			+ 2;
		to_return[i] = malloc(len * sizeof(char));
		if (!to_return[i])
		{
			while (i > 0)
				free(to_return[--i]);
			free(to_return);
			return (NULL);
		}
		ft_strlcpy_pars(to_return[i], current->name, len);
		ft_strlcat(to_return[i], "=", len);
		ft_strlcat(to_return[i], current->value, len);
		current = current->next;
		i++;
	}
	to_return[i] = NULL;
	return (to_return);
}
