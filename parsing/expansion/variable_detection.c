/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_detection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:43:46 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/26 13:52:48 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

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
	in_env = ft_strdup_pars(temp);
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
		if (ft_strncmp_pars(str, env[i], size) == 0 && env[i][size] == '=')
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
	commands->args[i] = ft_strdup_pars(str);
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
	while (str[i] && str[i] != '/' && str[i] != ' ' && str[i] != '\0')
	{
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	variable = ft_strdup_pars(temp);
	return (variable);
}

char	*extract_chain(char *str, int start, int end)
{
	int		size;
	char	*result;
	int		i;

	size = end - start;
	result = malloc((size + 1) * sizeof(char));
	i = 0;
	if (!result)
		return (NULL);
	while (start < end)
	{
		result[i] = str[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

char	*build_full_command(char *original, char **env, int exit_status)
{
	char	*result;
	char	*variable;
	char	*in_env;
	size_t	i;
	int		result_pos;
	size_t	j;
	int		k;
	char	*status_str;

	result = malloc(4096 * sizeof(char));
	i = 0;
	result_pos = 0;
	if (!result)
		return (NULL);
	while (i < ft_strlen_pars(original))
	{
		if (original[i] == '$')
		{
			j = i + 1;
			while (j < ft_strlen_pars(original) && ((original[j] >= 'a'
						&& original[j] <= 'z') || (original[j] >= 'A'
						&& original[j] <= 'Z') || (original[j] >= '0'
						&& original[j] <= '9') || original[j] == '_'))
				j++;
			variable = extract_chain(original, i + 1, j);
			if (ft_strcmp_pars(variable, "?") == 0)
			{
				status_str = ft_itoa_pars(exit_status);
				k = 0;
				while (status_str[k])
				{
					result[result_pos] = status_str[k];
					result_pos++;
					k++;
				}
				free(status_str);
				free(variable);
				i = j;
			}
			else
			{
				in_env = check_in_env(variable, env);
				if (in_env != NULL)
				{
					k = 0;
					while (in_env[k])
					{
						result[result_pos] = in_env[k];
						result_pos++;
						k++;
					}
				}
				free(variable);
				i = j;
			}
		}
		else
		{
			result[result_pos] = original[i];
			result_pos++;
			i++;
		}
	}
	result[result_pos] = '\0';
	return (result);
}

void	expansion(t_cmd *commands, char **env, int exit_status)
{
	char	*expanded;
	int		i;

	while (commands)
	{
		i = 0;
		while (commands->args[i])
		{
			if (is_variable(commands->args[i]) && !commands->args_single_quotes[i])
			{
				expanded = build_full_command(commands->args[i], env, exit_status);
				if (expanded)
				{
					replace_in_command(commands, expanded, i);
					free(expanded);
				}
			}
			i++;
		}
		if (commands->input_file && is_variable(commands->input_file) 
			&& !commands->input_single_quotes)
		{
			expanded = build_full_command(commands->input_file, env, exit_status);
			if (expanded)
			{
				free(commands->input_file);
				commands->input_file = ft_strdup_pars(expanded);
				free(expanded);
			}
		}
		if (commands->output_file && is_variable(commands->output_file) 
			&& !commands->output_single_quotes)
		{
			expanded = build_full_command(commands->output_file, env, exit_status);
			if (expanded)
			{
				free(commands->output_file);
				commands->output_file = ft_strdup_pars(expanded);
				free(expanded);
			}
		}
		if (commands->heredoc_delim && is_variable(commands->heredoc_delim) 
			&& !commands->heredoc_single_quotes)
		{
			expanded = build_full_command(commands->heredoc_delim, env, exit_status);
			if (expanded)
			{
				free(commands->heredoc_delim);
				commands->heredoc_delim = ft_strdup_pars(expanded);
				free(expanded);
			}
		}
		commands = commands->next;
	}
}
