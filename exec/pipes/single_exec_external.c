/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec_external.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:43:17 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/13 13:45:26 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static void	close_fds_if_needed(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}

static int	handle_path_not_found(t_cmd *cmd, int in_fd, int out_fd)
{
	close_fds_if_needed(in_fd, out_fd);
	fprintf(stderr, "%s: command not found\n", cmd->args[0]);
	return (127);
}

static void	execute_in_child(char *path, t_exec_ctx *ctx)
{
	char	**env_array;

	restore_signal();
	apply_redirs(ctx->in_fd, ctx->out_fd);
	env_array = env_list_to_array(ctx->env->env_list);
	execve(path, ctx->cmd->args, env_array);
	perror(path);
	free_tab(env_array);
	free(path);
	_exit(126);
}

static int	handle_wait_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	run_external_child(t_cmd *cmd, t_env *env)
{
	t_exec_ctx	ctx;
	pid_t		pid;
	int			status;
	char		*path;

	if (!setup_redirections(cmd, env, &ctx.in_fd, &ctx.out_fd))
		return (1);
	ctx.cmd = cmd;
	ctx.env = env;
	path = find_command_path(cmd->args[0], env->envp);
	if (!path)
		return (handle_path_not_found(cmd, ctx.in_fd, ctx.out_fd));
	pid = fork();
	if (pid == -1)
	{
		close_fds_if_needed(ctx.in_fd, ctx.out_fd);
		free(path);
		return (1);
	}
	if (pid == 0)
		execute_in_child(path, &ctx);
	free(path);
	close_fds_if_needed(ctx.in_fd, ctx.out_fd);
	waitpid(pid, &status, 0);
	return (handle_wait_status(status));
}
