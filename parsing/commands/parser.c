/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:59:22 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/24 11:25:39 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void add_arg(t_cmd *command, char *argument, int position)
{
    if (!command->args)
    {
        command->args = malloc(2 * sizeof(char*));
        if (!command->args)
        {
            printf("Error: malloc\n");
            return;
        }
    }
    else
    {
        command->args = realloc(command->args, ((position + 2) * sizeof(char*)));
        if (!command->args)
        {
            printf("Error: realloc\n");
            return;
        } 
    }
    command->args[position] = ft_strdup(argument);
    command->args[position + 1] = NULL;
}

bool redirection(t_cmd *command, types_tokens type, char *file)
{
    if (type == TOKEN_REDIRECT_IN)
    {
        if (command->input_file != NULL)
        {
            printf("Error: Multiple input files");
            return (false);
        }
        command->input_file = ft_strdup(file);
    }
    else if (type == TOKEN_REDIRECT_OUT)
    {
        if (command->output_file != NULL)
        {
            printf("Error: Multiple output files");
            return (false);
        }
        command->output_file = ft_strdup(file);
        command->append_mode = false;
    }
    else if (type == TOKEN_REDIRECT_APPEND)
    {
        if (command->output_file != NULL)
        {
            printf("Error: Multiple output files");
            return (false);
        }
        command->output_file = ft_strdup(file);
        command->append_mode = true;
    }
    else if (type == TOKEN_REDIRECT_HEREDOC)
    {
        if (command->heredoc_delim != NULL)
        {
            printf("Error: Multiple heredoc");
            return (false);
        }
        command->heredoc_delim = ft_strdup(file);
    }
    return (true);
}

t_cmd *parse_command(t_token **current)
{
    t_cmd *command = init_new_command();
    types_tokens current_type;
    int count = 0;

    while((*current) && (*current)->type != TOKEN_PIPE && (*current)->type != TOKEN_EOF)
    {
        if ((*current)->type == TOKEN_WORD)
        {
            add_arg(command, (*current)->value, count);
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
                return NULL;
            }
            else
            {
                if(!redirection(command, current_type, (*current)->value))
                    return NULL;
                (*current) = (*current)->next;
            }
        }
    }
    if (!command->args || !command->args[0])
    {
        printf("Error: Empty command or missing command name\n");
        return NULL;
    }
    if ((*current) && (*current)->type == TOKEN_PIPE)
        (*current) = (*current)->next;
    return (command);
}

t_cmd *parser_tokens(t_token *list)
{
    t_cmd *head = NULL;
    t_cmd *new_cmd = NULL;
    t_token *current = list;

    while(current)
    {
        if (current->type == TOKEN_EOF)
            break;
        new_cmd = parse_command(&current);
        if (!new_cmd)
        {
            printf("Error: Couldn't get new command");
            return NULL;
        }
        ft_lstadd_back_commands(&head, new_cmd);
    }
    return (head);
}
