/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:34:33 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/14 16:35:26 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_commands(t_cmd *commands)
{
	t_cmd	*current;
	t_cmd	*next;

	current = commands;
	while (current)
	{
		next = current->next;
		free_single_command(current);
		current = next;
	}
}

void	cleanup_env(t_env *env)
{
	if (!env)
		return ;
	if (env->current_input)
		free(env->current_input);
	if (env->current_cmd)
		free_commands(env->current_cmd);
	if (env->current_tokens)
		free_tokens(env->current_tokens);
	if (env->envp)
		free_tab(env->envp);
	if (env->pipeline_pids)
		free(env->pipeline_pids);
	if (env->env_list)
		ft_lstclear_pars(&env->env_list);
	free(env);
}
