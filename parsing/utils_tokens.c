/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:28:52 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/23 12:48:54 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_operator(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (true);
    else
        return (false);
}

bool is_quote(char c)
{
    if (c ==  39 || c == '"')
        return (true);
    else
        return (false);
}

char *extract_operator(char *str, int *i)
{
    int size;
    int j;
    int current;
    char *operator;
    
    current = *i;
    size = 0;
    while((str[current] == '|' || str[current] == '>' || str[current] == '<') && str[current] != '\0')
    {
        size++;
        current++;
    }
    operator = malloc((size + 1) * sizeof(char));
    if (!operator)
        return NULL;
    j = 0;
    while((str[*i] == '|' || str[*i] == '>' || str[*i] == '<') && str[*i] != '\0')
    {
        operator[j] = str[*i];
        (*i)++;
        j++;
    }
    operator[j] = '\0';
    return (operator);
}

char *extract_operator(char *str, int *i)
{
    
}