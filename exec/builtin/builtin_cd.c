/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:54:43 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/10 09:22:25 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

#include "../../header/parsing.h"

char	*get_target_directory(t_cmd *cmd, t_env *env)
{
	char	*pwd;

	if (!cmd->args[1])
		return (handle_home_directory(env));
	if (cmd->args[1][0] == '~' && cmd->args[1][1] == '\0')
		return (handle_home_directory(env));
	if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
		return (handle_oldpwd_directory(env));
	if (ft_strcmp_pars(cmd->args[1], "..") == 0)
	{
		pwd = get_env_value(env, "PWD");
		if (pwd)
			return (resolve_parent_dir(pwd));
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
	else
	{
		new_pwd = get_env_value(env, "PWD");
		if (new_pwd)
			set_env_var(env, "PWD", new_pwd);
	}
}

int	builtin_cd(t_cmd *cmd, t_env *env)
{
	char	*current_pwd;
	char	*target_dir;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		current_pwd = get_env_value(env, "PWD");
		if (!current_pwd)
			return (cd_error("cd: cannot determine current directory"));
		current_pwd = ft_strdup_pars(current_pwd);
	}
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
