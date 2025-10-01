/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:54:43 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/02 00:15:16 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

int	builtin_cd(t_cmd *cmd, t_env *env)
{
	char	*current_pwd;
	char	*target_dir;

	(void)cmd;
	(void)env;
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (cd_error("getcwd"));
	target_dir = get_target_directory(cmd, env);
	if (!target_dir)
	{
		free(current_pwd);
		return (1);
	}
	if (chdir(target_dir) != 0)
	{
		free(current_pwd);
		return (cd_error("cd"));
	}
	update_pwd_variables(env, current_pwd);
	free(current_pwd);
	return (0);
}

char	*get_target_directory(t_cmd *cmd, t_env *env)
{
	char	*home;
	char	*oldpwd;

	if (!cmd->args[1])
	{
		home = get_env_value(env, "HOME");
		if (!home)
		{
			cd_error("HOME not set");
			return (NULL);
		}
		return (home);
	}
	if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
	{
		oldpwd = get_env_value(env, "OLDPWD");
		if (!oldpwd)
		{
			cd_error("OLDPWD not set");
			return (NULL);
		}
		printf("%s\n", oldpwd);
		return (oldpwd);
	}
	return (cmd->args[1]);
}

void	update_pwd_variables(t_env *env, char *old_pwd)
{
	char	*new_pwd;

	set_env_var(env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_var(env, "PWD", new_pwd);  
		free(new_pwd);
	}
}
