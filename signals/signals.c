/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:39:34 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/30 16:02:11 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

void handle_sig_int_interactive(int signal)
{
    (void)signal;

    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sig_int_command(int signal)
{
    (void)signal;

    write(1, "\n", 1);
}

void handle_sig_quit(int signal)
{
    (void)signal;

    return ;
}

void setup_signals_interactive(void)
{
    signal(SIGINT, handle_sig_int_interactive);
    signal(SIGQUIT, SIG_IGN);
}

void setup_signals_command(void)
{
    signal(SIGINT, handle_sig_int_command);
    signal(SIGQUIT, SIG_IGN);
}

void restore_signal(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
