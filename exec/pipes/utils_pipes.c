/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:17:24 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/09 11:17:39 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

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

static int	exec_builtin_child(t_cmd *cmd, t_env *env)
{
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]))
		_exit(execute_builtin(cmd, env));
	return (0);
}

static void	exec_external_child(t_cmd *cmd, char **envp)
{
	char	*path;

	path = find_command_path(cmd->args[0], envp);
	if (!path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		free_tab(envp);
		_exit(127);
	}
	execve(path, cmd->args, envp);
	perror(path);
	free(path);
	free_tab(envp);
	_exit(126);
}

void	child_exec(t_cmd *cmd, t_env *env, int in_fd, int out_fd)
{
	char	**envp;

	restore_signal();
	apply_redirs(in_fd, out_fd);
	exec_builtin_child(cmd, env);
	envp = env_list_to_array(env->env_list);
	exec_external_child(cmd, envp);
}
