/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:11:55 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	trim(char **str, size_t len)
{
	char	*start;
	char	*end;
	char	*trimmed;

	if (!str || !*str)
		return ;
	start = *str;
	while (*start == ' ' || *start == '\t')
		start++;
	if (*start == '\0')
	{
		free(*str);
		*str = ft_strdup_pars("");
		return ;
	}
	end = start + ft_strlen_pars(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	len = end - start + 1;
	trimmed = (char *)malloc(len + 1);
	if (!trimmed)
		return ;
	ft_strlcpy_pars(trimmed, start, len + 1);
	free(*str);
	*str = trimmed;
}

bool	pre_check(char **str)
{
	trim(str, 0);
	if (check_if_empty(*str))
		return (false);
	if (check_quotes(*str))
		return (false);
	if (check_pipes(*str, 0))
		return (false);
	if (check_forbidden_sequences(*str))
		return (false);
	if (check_operators(*str, 0))
		return (false);
	return (true);
}
