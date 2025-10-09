/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:34:33 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/03 12:53:03 by lbolens          ###   ########.fr       */
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
	int		i;

	current = commands;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				free(current->args[i]);
				i++;
			}
			free(current->args);
		}
		if (current->args_single_quotes)
			free(current->args_single_quotes);
		if (current->input_file)
			free(current->input_file);
		if (current->output_file)
			free(current->output_file);
		if (current->all_output_files)
		{
			i = 0;
			while (i < current->output_count)
			{
				free(current->all_output_files[i]);
				i++;
			}
			free(current->all_output_files);
			free(current->all_output_append);
		}
		if (current->heredoc_delims)
		{
			i = 0;
			while (i < current->heredoc_count)
			{
				free(current->heredoc_delims[i]);
				i++;
			}
			free(current->heredoc_delims);
			free(current->heredoc_delim_quotes);
		}
		free(current);
		current = next;
	}
}
