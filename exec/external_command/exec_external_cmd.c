/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:34:52 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/09 11:07:40 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static int	wait_for_child(char *path)
{
	int	status;

	free(path);
	wait(&status);
	return (WEXITSTATUS(status));
}

static int	handle_fork_error(char *path)
{
	perror("fork");
	free(path);
	return (1);
}

int	execute_external_command(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	char	*path;

	path = find_command_path(cmd->args[0], env->envp);
	if (!path)
	{
		perror(cmd->args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		exec_child_process(path, cmd, env);
	else if (pid > 0)
		return (wait_for_child(path));
	else
		return (handle_fork_error(path));
	return (0);
}

void	exec_child_process(char *path, t_cmd *cmd, t_env *env)
{
	char	**env_array;

	restore_signal();
	env_array = env_list_to_array(env->env_list);
	execve(path, cmd->args, env_array);
	perror(path);
	free_tab(env_array);
	free(path);
	exit(126);
}
