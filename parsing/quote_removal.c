/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:42:58 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 14:43:05 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

void	quote_removal(t_cmd *commands)
{
	while (commands)
	{
		remove_quotes_from_args(commands);
		remove_quotes_from_input(commands);
		remove_quotes_from_outputs(commands);
		commands = commands->next;
	}
}
