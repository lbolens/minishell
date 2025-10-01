/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_custom_getenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:10:22 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/01 14:38:20 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

char *custom_getenv(char *key, t_env_var *env_vars)
{
    t_env_var *current = env_vars;

    if (!key)
        return (NULL);

    while (current)
    {
        if (ft_strcmp(current->name, key) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}
