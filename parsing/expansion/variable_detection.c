/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_detection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:43:46 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/25 11:11:47 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

bool	is_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char	*extract_in_env(char *str)
{
	int		i;
	int		j;
	char	temp[4096];
	char	*in_env;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	i++;
	while (str[i])
	{
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	in_env = ft_strdup(temp);
	return (in_env);
}

char	*check_in_env(char *str, char **env)
{
	int		i;
	int		size;
	char	*in_env;

	i = 0;
	size = 0;
	while (str[size])
		size++;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], size) == 0 && env[i][size] == '=')
		{
			in_env = extract_in_env(env[i]);
			return (in_env);
		}
		i++;
	}
	return (NULL);
}

void	replace_in_command(t_cmd *commands, char *str, int i)
{
	free(commands->args[i]);
	commands->args[i] = ft_strdup(str);
}

char *extract_variable(char *str)
{
    char *variable = NULL;
    char temp[4096];
    int i = 0;
    int j = 0;
    
    while(str[i] != '$' && str[i])
        i++;
    if (str[i] == '$')
        i++;
    while(str[i] && str[i] != '/' && str[i] != ' ' && str[i] != '\0')
    {
        temp[j] = str[i];
        j++;
        i++;
    }
    temp[j] = '\0';
    variable = ft_strdup(temp);
    return (variable);
}

void expansion(t_cmd *commands, char **env)
{
    char *variable;
    char *in_env;
    int i;
    
    while (commands)
    {
        i = 0;
        while (commands->args[i])
        {
            if (is_variable(commands->args[i]))
            {
                variable = extract_variable(commands->args[i]);
                if ((in_env = check_in_env(variable, env)) != NULL)
                {
                    replace_in_command(commands, in_env, i);
                }
                else
                {
                    // Variable inexistante -> remplacer par chaîne vide
                    replace_in_command(commands, "", i);
                }
                free(variable);
            }
            i++;
        }
        commands = commands->next;
    }
}
