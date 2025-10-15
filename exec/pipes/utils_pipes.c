/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:17:24 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/15 11:10:31 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	execute_cmd_pipeline(t_cmd *cmd_list, t_env *env)
{
	t_cmd	*only;

	if (!cmd_list)
		return (0);
	only = cmd_list;
	if (!only->next && only->args && only->args[0] && is_builtin(only->args[0]))
		return (run_builtin_parent(only, env));
	return (execute_pipeline(cmd_list, env));
}

void	close_if_valid(int fd)
{
	if (fd >= 0)
		close(fd);
}

static void	exec_error(char *path, char **envp, t_env *env, int code)
{
	perror(path);
	free(path);
	free_tab(envp);
	cleanup_env(env);
	exit(code);
}

void	child_exec(t_cmd *cmd, t_env *env, int in_fd, int out_fd)
{
	char	**envp;
	char	*path;
	int		status;

	restore_signal();
	apply_redirs(in_fd, out_fd);
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
	{
		status = execute_builtin(cmd, env);
		cleanup_env(env);
		exit(status);
	}
	envp = env_list_to_array(env->env_list);
	path = find_command_path(cmd->args[0], envp);
	if (!path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		free_tab(envp);
		cleanup_env(env);
		exit(127);
	}
	execve(path, cmd->args, envp);
	exec_error(path, envp, env, 126);
}
