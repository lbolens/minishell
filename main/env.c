/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:43:19 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/26 16:11:08 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

t_env_var	*envp_to_env_list(char **envp)
{
	t_env_var	*head;
	t_env_var	*new_var;
	t_env_var	*tmp;
	char		*equal_pos;
	int			i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		equal_pos = ft_strchr(envp[i], '=');
		if (equal_pos)
		{
			new_var = malloc(sizeof(t_env_var));
			if (!new_var)
				return (NULL);
			new_var->key = ft_substr(envp[i], 0, equal_pos - envp[i]);
			new_var->value = ft_strdup(equal_pos + 1);
			new_var->is_exported = true;
			new_var->next = NULL;
			if (!head)
				head = new_var;
			else
			{
				tmp = head;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new_var;
			}
		}
		i++;
	}
	return (head);
}

void	set_env_var(t_env_var **env_vars, char *key, char *value,
		bool is_exported)
{
	t_env_var	*current;
	t_env_var	*new_var;

	if (!key)
		return ;
	current = *env_vars;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = ft_strdup("");
			current->is_exported = is_exported;
			return ;
		}
		current = current->next;
	}
	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = ft_strdup("");
	new_var->is_exported = is_exported;
	new_var->next = *env_vars;
	*env_vars = new_var;
}

void unset_env_var(t_env_var **env_vars, char *key)
{
    t_env_var *current = *env_vars;
    t_env_var *prev = NULL;

    if (!key)
        return;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env_vars = current->next;

            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Reconvertir en char ** pour execve()
char **env_list_to_envp(t_env_var *env_vars)
{
    t_env_var *current = env_vars;
    char **envp;
    int count = 0;
    int i = 0;

    // Compter les variables exportées
    while (current)
    {
        if (current->is_exported)
            count++;
        current = current->next;
    }

    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL);

    current = env_vars;
    while (current)
    {
        if (current->is_exported)
        {
            int key_len = ft_strlen(current->key);
            int val_len = ft_strlen(current->value);
            
            envp[i] = malloc(key_len + val_len + 2); // +2 pour '=' et '\0'
            if (!envp[i])
                return (envp);

            ft_strcpy(envp[i], current->key);
            ft_strcat(envp[i], "=");
            ft_strcat(envp[i], current->value);
            i++;
        }
        current = current->next;
    }
    envp[i] = NULL;
    return (envp);
}

// Afficher les variables exportées (pour export sans arguments)
void print_exported_vars(t_env_var *env_vars)
{
    t_env_var *current = env_vars;

    while (current)
    {
        if (current->is_exported)
        {
            printf("declare -x %s=\"%s\"\n", current->key, current->value);
        }
        current = current->next;
    }
}

// Libérer la mémoire de la liste
void free_env_list(t_env_var *env_vars)
{
    t_env_var *current = env_vars;
    t_env_var *next;

    while (current)
    {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
}

// Initialiser l'environnement avec la nouvelle structure
t_env *init_exec_env_new(char **envp)
{
    t_env *env = malloc(sizeof(t_env));
    if (!env)
        return (NULL);

    env->env_vars = envp_to_env_list(envp);
    env->exit_status = 0;
    env->stdin_backup = -1;
    env->stdout_backup = -1;

    return (env);
}

// Libérer l'environnement d'exécution
void free_exec_env_new(t_env *env)
{
    if (!env)
        return;

    free_env_list(env->env_vars);
    
    if (env->stdin_backup != -1)
        close(env->stdin_backup);
    if (env->stdout_backup != -1)
        close(env->stdout_backup);

    free(env);
}