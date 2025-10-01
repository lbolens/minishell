/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:17:24 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/01 16:17:13 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

void	close_if_valid(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	apply_io(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
}

int	execute_cmd_pipeline(t_cmd *cmd_list, t_env *env)
{
	t_cmd *only;

	if (!cmd_list)
		return (0);
	only = cmd_list;
	if (!only->next && only->args && only->args[0] && is_builtin(only->args[0]))
		return (run_single_builtin_in_parent(only, env));
	return (run_pipeline(cmd_list, env));
}