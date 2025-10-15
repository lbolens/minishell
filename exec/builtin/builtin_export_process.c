/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:06:34 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 14:44:28 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*get_new_value_append(char *old_value, char *value)
{
	char	*new_value;

	if (old_value && value)
		new_value = ft_strjoin(old_value, value);
	else if (value)
		new_value = ft_strdup_pars(value);
	else
		new_value = ft_strdup_pars("");
	return (new_value);
}

static void	handle_append_mode(char *var, char *value, t_env *env)
{
	char	*old_value;
	char	*new_value;

	old_value = get_env_value(env, var);
	new_value = get_new_value_append(old_value, value);
	set_env_var(env, var, new_value);
	free(new_value);
}

static void	handle_normal_mode(char *var, char *value, t_env *env)
{
	if (value != NULL)
		set_env_var(env, var, value);
	else
		declare_env_var(env, var);
}

static void	cleanup_export(char *var, char *value, char *cleaned_arg)
{
	free(var);
	if (value)
		free(value);
	free(cleaned_arg);
}

int	process_single_export(char *arg, t_env *env)
{
	char	*var;
	char	*value;
	char	*cleaned_arg;

	cleaned_arg = remove_quotes(arg);
	if (!cleaned_arg || !parse_export(cleaned_arg))
	{
		ft_printf("Error: variable error\n");
		free(cleaned_arg);
		return (1);
	}
	var = extract_var(cleaned_arg);
	value = extract_value(cleaned_arg);
	if (is_append_mode(cleaned_arg))
		handle_append_mode(var, value, env);
	else
		handle_normal_mode(var, value, env);
	cleanup_export(var, value, cleaned_arg);
	return (0);
}
