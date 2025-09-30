/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_manip_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:21:37 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/30 13:05:10 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

t_env_var	*create_new_env_var(char *str, char *value)
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

// Ajouter variable a la liste
void	add_env_var(t_env_var **list, char *env_string)
{
	t_env_var	*temp;
	t_env_var	*new;

	new = create_new_env_var(env_string);
	if (!list || !new)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

// Chercher une variable
char	*get_env_value(t_env *env, char *name)
{
    t_env_var *current;
    
    if (!env || !name)
        return NULL;
    current = env->env_list;
    while(current)
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
    t_env_var *current;
    char *new_value;
    char *env_string;

    if (!env || !name || !value)
        return ;
    current = env->env_list;
    while(current)
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
    ft_strlcat(env_string, value, ft_strlen_pars(name) + ft_strlen_pars(value) + 2);
    add_env_var(&env->env_list, env_string);
    free(env_string);
}

// Supprimer une variable (pour unset)
void	unset_env_var(t_env *env, char *name)
{
}

// Convertir la liste en char** pour execve
char	**env_list_to_array(t_env_var *list)
{
}
