/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:11:37 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:10:08 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_heredoc_sigint(int signal)
{
	(void)signal;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_heredoc_signals(t_env *env)
{
	(void)env;
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
