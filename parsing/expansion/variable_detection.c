/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_detection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:43:46 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/24 15:14:56 by lbolens          ###   ########.fr       */
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

char	*extract_variable(char *str)
{
	char	*variable;
	char	temp[4096];
	int		i;
	int		j;

	variable = NULL;
	i = 0;
	j = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (str[i] == '$')
		i++;
	while (str[i] && str[i] != '/' && str[i] != ' ')
	{
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	variable = ft_strdup(temp);
	return (variable);
}

void	replace_in_command(t_cmd *commands, char *str, int i)
{
	free(commands->args[i]);
	commands->args[i] = ft_strdup(str);
}

bool check_if_simple(char *str)
{
    int i;
    int conditions;
    
    i = 0;
    conditions = 0;
    while(str[i])
    {
        if (str[i] == '$')
            if (i == 0)
                conditions++; // check si le $ est au debut
    }
    while(i--)
    {
        if (str[i] == 92) //check si il n y a pas de "\"
            conditions--;
    }
    if (conditions == 1)
        return (true);
    return (false);
}

char *split_env(char *str)
{
    int i;
    int j;
    char temp[4096];
    char *splitted;

    i = 0;
    j = 0;
    if (str[i] != '$')
    {
        while(str[i] != '$' && str[i])
        {
            temp[i] = str[i];
            i++;
        }
        temp[i]= '\0';
    }
    else
    {
        while(str[i] != 92)
            i++;
        while(str[i])
        {
            temp[j] = str[i];
            j++;
            i++;
        }
        temp[j] = '\0';
    }
    splitted = ft_strdup(temp);
    return (splitted);    
}

void	expansion(t_cmd *commands, char **env)
{
	char *variable;
	char *in_env;
    char *split_variable;
	int i;
	variable = NULL;
	in_env = NULL;
    split_variable = NULL;
	while (commands)
	{
		i = 0;
		while (commands->args[i])
		{
			if (is_variable(commands->args[i]) && check_if_simple(commands->args[i]))
			{
				variable = extract_variable(commands->args[i]);
				if ((in_env = check_in_env(variable, env)) != NULL)
					replace_in_command(commands, in_env, i);
                else if ((in_env = check_in_env(variable, env)) == NULL)
                {
                    //A implementer
                }
				free(variable);
			}
            else if (is_variable(commands->args[i]) && !(check_if_simple(commands->args[i])))
            {
                split_variable = split_env(commands->args[i]);
                /*
                La, je split juste pour avoir soit avant ou apres le $XXX mais je ne sais pas encore
                si c est avant ou apres. Il faut encore mettre ca pour savoir apres pour join.
                */
                variable = extract_variable(commands->args[i]);
				if ((in_env = check_in_env(variable, env)) != NULL)
                {
                    //Mettre une fonction pour join split_varibale et variable   
					replace_in_command(commands, in_env, i);
                }
                else if ((in_env = check_in_env(variable, env)) == NULL)
                {
                    //A implementer
                }
				free(variable);
                
            }
			i++;
		}
		commands = commands->next;
	}
}
