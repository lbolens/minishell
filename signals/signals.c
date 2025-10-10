/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:39:34 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/10 09:45:22 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

/*void	handle_sig_int_command(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}*/

/*void	handle_sig_quit(int signal)
{
	(void)signal;
	return ;
}*/

void	setup_signals_interactive(void)
{
	signal(SIGINT, handle_sig_int_interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_command(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
