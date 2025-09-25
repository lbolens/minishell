/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:00:11 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/25 11:28:11 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

types_tokens	define_type(char *str)
{
	if (!str)
		return (TOKEN_EOF);
	if (ft_strcmp(str, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(str, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (TOKEN_REDIRECT_APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	else
		return (TOKEN_WORD);
}
