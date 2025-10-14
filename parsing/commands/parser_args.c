/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:54:26 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 11:54:40 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static int	init_args_arrays(t_cmd *command)
{
	command->args = malloc(2 * sizeof(char *));
	command->args_single_quotes = malloc(2 * sizeof(bool));
	if (!command->args || !command->args_single_quotes)
	{
		printf("Error: malloc\n");
		if (command->args)
			free(command->args);
		if (command->args_single_quotes)
			free(command->args_single_quotes);
		command->args = NULL;
		command->args_single_quotes = NULL;
		return (0);
	}
	return (1);
}

static int	realloc_args_arrays(t_cmd *command, int position)
{
	char	**new_args;
	bool	*new_quotes;

	new_args = realloc(command->args, ((position + 2) * sizeof(char *)));
	new_quotes = realloc(command->args_single_quotes,
			((position + 2) * sizeof(bool)));
	if (!new_args || !new_quotes)
	{
		printf("Error: realloc\n");
		if (new_args)
			command->args = new_args;
		if (new_quotes)
			command->args_single_quotes = new_quotes;
		return (0);
	}
	command->args = new_args;
	command->args_single_quotes = new_quotes;
	return (1);
}

static void	fill_arg_data(t_cmd *command, char *argument, bool is_single_quote,
		int position)
{
	command->args[position] = ft_strdup_pars(argument);
	command->args_single_quotes[position] = is_single_quote;
	command->args[position + 1] = NULL;
	command->args_count = position + 1;
}

void	add_arg(t_cmd *command, char *argument, bool is_single_quote,
		int position)
{
	if (!command->args)
	{
		if (!init_args_arrays(command))
			return ;
	}
	else
	{
		if (!realloc_args_arrays(command, position))
			return ;
	}
	fill_arg_data(command, argument, is_single_quote, position);
}
