/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/23 11:16:10 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void trim(char **str)
{
    char *start;
    char *end;
    char *trimmed;
    size_t len;

    if (!str || !*str)
        return ;
    start = *str;
    while (*start == ' ' || *start == '\t')
        start++;
    if (*start == '\0')
    {
        free(*str);
        *str = ft_strdup("");
        return ;
    }
    end = start + ft_strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t'))
        end--;
    len = end - start + 1;
    trimmed = (char *)malloc(len + 1);
    if (!trimmed)
        return ;
    ft_strlcpy(trimmed, start, len + 1);
    free(*str);
    *str = trimmed;
}

bool pre_check(char **str)
{
    trim(str);
    
    if (check_if_empty(*str))
        return (false);
    if (check_quotes(*str))
        return (false);
    if (check_pipes(*str))
        return (false);
    if (check_forbidden_sequences(*str))
        return (false);
    if (check_operators(*str))
        return (false);
    return (true);
}
