/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:22:03 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 14:22:44 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

void	handle_quote_state(char c, char *current_quote, char *result,
		int *result_pos)
{
	if (c == '"' && *current_quote == 0)
		*current_quote = '"';
	else if (c == 39 && *current_quote == 0)
		*current_quote = 39;
	else if (c == *current_quote)
		*current_quote = 0;
	result[(*result_pos)++] = c;
}

void	append_exit_status(t_env *env, char *result, int *result_pos)
{
	char	*status_str;
	int		k;

	status_str = ft_itoa_pars(env->exit_status);
	k = 0;
	while (status_str[k])
	{
		result[*result_pos] = status_str[k];
		(*result_pos)++;
		k++;
	}
	free(status_str);
}
