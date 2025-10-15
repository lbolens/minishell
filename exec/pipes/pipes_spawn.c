/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:16:31 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:10:18 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	setup_pipe_fds(t_cmd *cmd, t_env *env, int *p)
{
	int	in_fd;
	int	out_fd;

	if (!setup_redirections(cmd, env, &in_fd, &out_fd))
		return (0);
	p[2] = in_fd;
	p[3] = out_fd;
	return (1);
}

static pid_t	fork_and_exec(t_cmd *cmd, t_env *env, int *p)
{
	pid_t	pid;
	int		has_next;

	has_next = (p[0] != -1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (has_next)
			close(p[0]);
		child_exec(cmd, env, p[2], p[3]);
	}
	return (pid);
}

static int	handle_spawn_error(t_cmd *cmd, int *p)
{
	if (cmd->next)
	{
		close(p[0]);
		close(p[1]);
	}
	return (-1);
}

static void	finalize_spawn(t_cmd *cmd, int *p, int *next_in)
{
	if (cmd->next)
		*next_in = p[0];
	else
		*next_in = -1;
}

int	spawn(t_cmd *cmd, t_env *env, int last_in, int *next_in)
{
	int		p[4];
	pid_t	pid;

	p[0] = -1;
	p[1] = -1;
	if (cmd->next && pipe(p) == -1)
		return (-1);
	if (!setup_pipe_fds(cmd, env, p))
		return (handle_spawn_error(cmd, p));
	adjust_fds(&p[2], &p[3], last_in, p);
	pid = fork_and_exec(cmd, env, p);
	if (pid == -1)
		return (handle_spawn_error(cmd, p));
	cleanup_fds(p[2], p[3], last_in, p[1]);
	finalize_spawn(cmd, p, next_in);
	return (pid);
}
