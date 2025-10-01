/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:34:52 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/30 16:04:13 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

int	execute_external_command(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
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
	{
		free(path);
		wait(&status);
		return (WEXITSTATUS(status));
	}
	else
	{
		perror("fork");
		free(path);
		return (1);
	}
    return (0);
}

void	exec_child_process(char *path, t_cmd *cmd, t_env *env)
{
	char **env_array;
	
	restore_signal();
	env_array = env_list_to_array(env->env_list);
	execve(path, cmd->args, env_array);
	perror(path);
	free_tab(env_array);
	free(path);
	exit(126);
}
