/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:01:11 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/24 11:09:46 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void print_commands(t_cmd *commands)
{
    int cmd_num = 1;
    
    while (commands)  // ✅ Traite toutes les commandes, y compris la dernière
    {
        printf("Command %d:\n", cmd_num);
        
        // Afficher les arguments
        if (commands->args)
        {
            printf("  Args: ");
            int i = 0;
            while (commands->args[i])
            {
                printf("[%s] ", commands->args[i]);
                i++;
            }
            printf("\n");
        }
        
        // Afficher les redirections
        if (commands->input_file)
            printf("  Input: %s\n", commands->input_file);
        if (commands->output_file)
            printf("  Output: %s (append: %s)\n", 
                   commands->output_file, 
                   commands->append_mode ? "yes" : "no");
        if (commands->heredoc_delim)
            printf("  Heredoc: %s\n", commands->heredoc_delim);
            
        printf("---\n");
        commands = commands->next;
        cmd_num++;
    }
}

int main(void)
{
    char *input = readline("minishell> ");  // ✅ Avec prompt
    
    if (!input)  // ✅ Vérification NULL
    {
        printf("Error reading input\n");
        return 1;
    }
    
    if (pre_check(&input))
    {
        t_token *tokens = tokenization(input);
        if (!tokens)
        {
            printf("Tokenization failed\n");
            //free(input);
            return 1;
        }
        
        t_cmd *commands = parser_tokens(tokens);
        if (!commands)
        {
            printf("Parsing failed\n");
            //free(input);
            return 1;
        }
        
        print_commands(commands);
        
        // TODO: Libérer la mémoire (tokens et commands)
    }
    else
    {
        printf("Pre-check failed\n");
    }
    
    //free(input);
    return 0;
}