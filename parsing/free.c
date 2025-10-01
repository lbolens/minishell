/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:34:33 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/26 15:34:46 by lbolens          ###   ########.fr       */
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
		// Libérer les arguments
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
		// Libérer le tableau de quotes
		if (current->args_single_quotes)
			free(current->args_single_quotes);
		// Libérer les fichiers
		if (current->input_file)
			free(current->input_file);
		if (current->output_file)
			free(current->output_file);
		if (current->heredoc_delim)
			free(current->heredoc_delim);
		free(current);
		current = next;
	}
}
