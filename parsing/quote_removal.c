/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:42:58 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/14 15:35:06 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

static void	remove_quotes_from_heredoc_delims(t_cmd *commands)
{
	char	*no_quotes;
	int		j;

	if (!commands->heredoc_delims || commands->heredoc_count <= 0)
		return ;
	j = 0;
	while (j < commands->heredoc_count)
	{
		no_quotes = remove_quotes_from_string(commands->heredoc_delims[j]);
		if (no_quotes)
		{
			free(commands->heredoc_delims[j]);
			commands->heredoc_delims[j] = no_quotes;
		}
		j++;
	}
}

void	quote_removal(t_cmd *commands)
{
	while (commands)
	{
		remove_quotes_from_args(commands);
		remove_quotes_from_input(commands);
		remove_quotes_from_outputs(commands);
		remove_quotes_from_heredoc_delims(commands);
		commands = commands->next;
	}
}
