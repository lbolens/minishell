/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:05:44 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:11:46 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	expand_args(t_cmd *commands, t_env *env)
{
	char	*expanded;
	int		i;

	i = 0;
	while (commands->args[i])
	{
		if (is_variable(commands->args[i]) && !commands->args_single_quotes[i])
		{
			expanded = build_full_command(commands->args[i], env, 0, false);
			if (expanded)
			{
				replace_in_command(commands, expanded, i);
				free(expanded);
			}
		}
		i++;
	}
}

static void	expand_input_file(t_cmd *commands, t_env *env)
{
	char	*expanded;

	if (commands->input_file && is_variable(commands->input_file)
		&& !commands->input_single_quotes)
	{
		expanded = build_full_command(commands->input_file, env, 0, false);
		if (expanded)
		{
			free(commands->input_file);
			commands->input_file = ft_strdup_pars(expanded);
			free(expanded);
		}
	}
}

static void	expand_output_file(t_cmd *commands, t_env *env)
{
	char	*expanded;

	if (commands->output_file && is_variable(commands->output_file)
		&& !commands->output_single_quotes)
	{
		expanded = build_full_command(commands->output_file, env, 0, false);
		if (expanded)
		{
			free(commands->output_file);
			commands->output_file = ft_strdup_pars(expanded);
			free(expanded);
		}
	}
}

void	expansion(t_cmd *commands, t_env *env)
{
	while (commands)
	{
		expand_args(commands, env);
		expand_input_file(commands, env);
		expand_output_file(commands, env);
		commands = commands->next;
	}
}
