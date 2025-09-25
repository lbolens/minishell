/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:34:52 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 16:11:07 by hlongin          ###   ########.fr       */
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
	execve(path, cmd->args, env->envp);
	perror(path);
	free(path);
	exit(126);
}
