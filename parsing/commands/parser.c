/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:59:22 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 11:56:01 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static int	handle_word_token(t_token **current, t_cmd *command, int *count)
{
	add_arg(command, (*current)->value, (*current)->single_quotes, *count);
	(*count)++;
	(*current) = (*current)->next;
	return (1);
}

static int	handle_redir_token(t_token **current, t_cmd *command)
{
	t_types_tokens	current_type;
	bool			redir_is_single;

	current_type = (*current)->type;
	(*current) = (*current)->next;
	if (!(*current) || (*current)->type != TOKEN_WORD)
	{
		printf("Error: No file after redirection");
		return (0);
	}
	redir_is_single = (*current)->single_quotes;
	if (!redirection(command, current_type, (*current)->value, redir_is_single))
		return (0);
	(*current) = (*current)->next;
	return (1);
}

static int	parse_tokens_loop(t_token **current, t_cmd *command)
{
	int	count;

	count = 0;
	while ((*current) && (*current)->type != TOKEN_PIPE
		&& (*current)->type != TOKEN_EOF)
	{
		if ((*current)->type == TOKEN_WORD)
		{
			if (!handle_word_token(current, command, &count))
				return (0);
		}
		else if (is_redirection(*current))
		{
			if (!handle_redir_token(current, command))
				return (0);
		}
	}
	return (1);
}

t_cmd	*parse_command(t_token **current)
{
	t_cmd	*command;

	command = init_new_command();
	if (!command)
		return (NULL);
	if (!parse_tokens_loop(current, command))
	{
		free_commands(command);
		return (NULL);
	}
	if (!command->args || !command->args[0])
	{
		printf("Error: Empty command or missing command name\n");
		free_commands(command);
		return (NULL);
	}
	if ((*current) && (*current)->type == TOKEN_PIPE)
		(*current) = (*current)->next;
	return (command);
}

t_cmd	*parser_tokens(t_token *list)
{
	t_cmd	*head;
	t_cmd	*new_cmd;
	t_token	*current;

	head = NULL;
	new_cmd = NULL;
	current = list;
	while (current)
	{
		if (current->type == TOKEN_EOF)
			break ;
		new_cmd = parse_command(&current);
		if (!new_cmd)
		{
			printf("Error: Couldn't get new command");
			return (NULL);
		}
		ft_lstadd_back_commands(&head, new_cmd);
	}
	return (head);
}
