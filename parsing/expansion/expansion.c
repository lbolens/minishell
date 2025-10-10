/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:05:44 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/10 15:31:06 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

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

/*static void	expand_heredoc_delims(t_cmd *commands, t_env *env)
{
	char	*expanded;
	int		j;

	if (!commands->heredoc_delims || commands->heredoc_count <= 0)
		return ;
	j = 0;
	while (j < commands->heredoc_count)
	{
		if (is_variable(commands->heredoc_delims[j])
			&& !commands->heredoc_delim_quotes[j])
		{
			expanded = build_full_command(commands->heredoc_delims[j], env, 0,
					false);
			if (expanded)
			{
				free(commands->heredoc_delims[j]);
				commands->heredoc_delims[j] = ft_strdup_pars(expanded);
				free(expanded);
			}
		}
		j++;
	}
}*/

void	expansion(t_cmd *commands, t_env *env)
{
	while (commands)
	{
		expand_args(commands, env);
		expand_input_file(commands, env);
		expand_output_file(commands, env);
		//expand_heredoc_delims(commands, env);
		commands = commands->next;
	}
}
