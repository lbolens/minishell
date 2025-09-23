/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:30:14 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/23 12:33:51 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *tokenization(char *str)
{
    t_token *head = NULL;
    t_token *new_token = NULL;
    char *token;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while(str[i])
    {
        if (str[i] == ' ' || str[i] == '\t')
            i++;
        else if  (is_operator(str[i]))
            token = extract_operator(str, &i);
        else if (is_quote(str[i]))
            token = extract_quote(str, &i);
        else
            token = extract_word(str, &i);
        new_token = ft_lstnew(token);
        ft_lstadd_back(&head, new_token);
    }
    return (head);   
}
