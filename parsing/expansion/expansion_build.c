/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:05:23 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 15:38:44 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static void	append_env_value(char *variable, t_env *env, char *result,
		int *result_pos)
{
	char	*in_env;
	int		k;

	in_env = get_env_value(env, variable);
	if (in_env != NULL)
	{
		k = 0;
		while (in_env[k])
		{
			result[*result_pos] = in_env[k];
			(*result_pos)++;
			k++;
		}
	}
}

static size_t	handle_exit_status_var(size_t j, t_build_data *data)
{
	append_exit_status(data->env, data->result, data->result_pos);
	return (j + 1);
}

static size_t	handle_env_var(char *original, size_t i, size_t j,
		t_build_data *data)
{
	char	*variable;

	while (j < ft_strlen_pars(original) && ((original[j] >= 'a'
				&& original[j] <= 'z') || (original[j] >= 'A'
				&& original[j] <= 'Z') || (original[j] >= '0'
				&& original[j] <= '9') || original[j] == '_'))
		j++;
	variable = extract_chain(original, i + 1, j);
	append_env_value(variable, data->env, data->result, data->result_pos);
	free(variable);
	return (j);
}

static size_t	process_dollar_sign(char *original, size_t i,
		t_build_data *data)
{
	size_t	j;

	j = i + 1;
	if (j < ft_strlen_pars(original) && original[j] == '?')
		return (handle_exit_status_var(j, data));
	else if (j < ft_strlen_pars(original) && ((original[j] >= 'a'
				&& original[j] <= 'z') || (original[j] >= 'A'
				&& original[j] <= 'Z') || original[j] == '_'))
		return (handle_env_var(original, i, j, data));
	data->result[(*data->result_pos)++] = original[i];
	return (i + 1);
}

char	*build_full_command(char *original, t_env *env, size_t i,
		bool heredoc_mode)
{
	t_build_data	data;
	int				result_pos;
	char			current_quote;

	data.result = malloc(4096 * sizeof(char));
	if (!data.result)
		return (NULL);
	data.original = original;
	data.env = env;
	data.result_pos = &result_pos;
	result_pos = 0;
	current_quote = 0;
	while (i < ft_strlen_pars(original))
	{
		if (!heredoc_mode && (original[i] == '"' || original[i] == 39)
			&& (current_quote == 0 || original[i] == current_quote))
			handle_quote_state(original[i++], &current_quote, data.result,
				&result_pos);
		else if (original[i] == '$' && (heredoc_mode || current_quote != 39))
			i = process_dollar_sign(original, i, &data);
		else
			data.result[result_pos++] = original[i++];
	}
	data.result[result_pos] = '\0';
	return (data.result);
}
