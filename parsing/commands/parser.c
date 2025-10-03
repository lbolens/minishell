/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:59:22 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/03 12:49:22 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

void	add_arg(t_cmd *command, char *argument, bool is_single_quote,
		int position)
{
	if (!command->args)
	{
		command->args = malloc(2 * sizeof(char *));
		command->args_single_quotes = malloc(2 * sizeof(bool));
		if (!command->args || !command->args_single_quotes)
		{
			printf("Error: malloc\n");
			return ;
		}
	}
	else
	{
		command->args = realloc(command->args, ((position + 2)
					* sizeof(char *)));
		command->args_single_quotes = realloc(command->args_single_quotes,
				((position + 2) * sizeof(bool)));
		if (!command->args || !command->args_single_quotes)
		{
			printf("Error: realloc\n");
			return ;
		}
	}
	command->args[position] = ft_strdup_pars(argument);
	command->args_single_quotes[position] = is_single_quote;
	command->args[position + 1] = NULL;
	command->args_count = position + 1;
}

bool	redirection(t_cmd *command, types_tokens type, char *file,
		bool is_single_quote)
{
	if (type == TOKEN_REDIRECT_IN)
	{
		if (command->input_file != NULL)
			free(command->input_file);
		command->input_file = ft_strdup_pars(file);
		command->input_single_quotes = is_single_quote;
	}
	else if (type == TOKEN_REDIRECT_OUT)
	{
		if (command->output_file != NULL)
			free(command->output_file);
		command->output_file = ft_strdup_pars(file);
		command->output_single_quotes = is_single_quote;
		command->append_mode = false;
	}
	else if (type == TOKEN_REDIRECT_APPEND)
	{
		if (command->output_file != NULL)
			free(command->output_file);
		command->output_file = ft_strdup_pars(file);
		command->output_single_quotes = is_single_quote;
		command->append_mode = true;
	}
	else if (type == TOKEN_REDIRECT_HEREDOC)
	{
		command->heredoc_delims = realloc(command->heredoc_delims,
				(command->heredoc_count + 1) * sizeof(char *));
		command->heredoc_delim_quotes = realloc(command->heredoc_delim_quotes,
				(command->heredoc_count + 1) * sizeof(bool));
		if (!command->heredoc_delims || !command->heredoc_delim_quotes)
			return (false);
		command->heredoc_delims[command->heredoc_count] = ft_strdup_pars(file);
		command->heredoc_delim_quotes[command->heredoc_count] = is_single_quote;
		command->heredoc_count++;
	}
	return (true);
}

t_cmd	*parse_command(t_token **current)
{
	t_cmd			*command;
	types_tokens	current_type;
	bool			redir_is_single;
	int				count;

	command = init_new_command();
	if (!command)
		return (NULL);
	count = 0;
	while ((*current) && (*current)->type != TOKEN_PIPE
		&& (*current)->type != TOKEN_EOF)
	{
		if ((*current)->type == TOKEN_WORD)
		{
			add_arg(command, (*current)->value, (*current)->single_quotes,
				count);
			count++;
			(*current) = (*current)->next;
		}
		else if (is_redirection(*current))
		{
			current_type = (*current)->type;
			(*current) = (*current)->next;
			if (!(*current) || (*current)->type != TOKEN_WORD)
			{
				printf("Error: No file after redirection");
				free_commands(command);
				return (NULL);
			}
			else
			{
				redir_is_single = (*current)->single_quotes;
				if (!redirection(command, current_type, (*current)->value,
						redir_is_single))
				{
					free_commands(command);
					return (NULL);
				}
				(*current) = (*current)->next;
			}
		}
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
