/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:00:11 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/23 12:06:50 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

types_tokens define_value(char *str)
{
    types_tokens *type;

    if (str == "|")
        type = 1;
    else if (str == "<")
        type = 2;
    else if (str == ">")
        type = 3;
    else if (str == ">>")
        type = 4;
    else if (str == "<<")
        type = 5;
    else if (str == NULL)
        type = 6;
    else
        type = 0;
    return (type);
}
