/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:23:36 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:10:38 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	cleanup_fds(int in_fd, int out_fd, int last_in, int pipe_w)
{
	if (in_fd != STDIN_FILENO && in_fd != last_in)
		close_if_valid(in_fd);
	if (out_fd != STDOUT_FILENO && out_fd != pipe_w)
		close_if_valid(out_fd);
	if (last_in >= 0)
		close_if_valid(last_in);
	if (pipe_w >= 0)
		close(pipe_w);
}

void	adjust_fds(int *in_fd, int *out_fd, int last_in, int *p)
{
	int	has_next;

	has_next = (p[0] != -1);
	if (*in_fd == STDIN_FILENO && last_in >= 0)
		*in_fd = last_in;
	if (*out_fd == STDOUT_FILENO && has_next)
		*out_fd = p[1];
}
