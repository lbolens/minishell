/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:54:43 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/10 09:16:15 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static char	*resolve_parent_dir(char *pwd)
{
	char	*last_slash;
	char	*parent;
	int		len;

	if (!pwd || ft_strcmp_pars(pwd, "/") == 0)
		return (ft_strdup_pars("/"));
	last_slash = ft_strrchr(pwd, '/');
	if (!last_slash || last_slash == pwd)
		return (ft_strdup_pars("/"));
	len = last_slash - pwd;
	parent = malloc(len + 1);
	if (!parent)
		return (NULL);
	ft_strlcpy_pars(parent, pwd, len + 1);
	return (parent);
}

static char	*get_target_directory(t_cmd *cmd, t_env *env)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;

	if (!cmd->args[1])
		return (handle_home_directory(env));
	if (cmd->args[1][0] == '~' && cmd->args[1][1] == '\0')
		return (handle_home_directory(env));
	if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
		return (handle_oldpwd_directory(env));
	// Gérer cd .. quand le répertoire courant n'existe plus
	if (ft_strcmp_pars(cmd->args[1], "..") == 0)
	{
		pwd = get_env_value(env, "PWD");
		if (pwd)
			return (resolve_parent_dir(pwd));
	}
	return (cmd->args[1]);
}

int	builtin_cd(t_cmd *cmd, t_env *env)
{
	char	*current_pwd;
	char	*target_dir;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		// Fallback: utiliser la variable PWD si getcwd échoue
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

static char	*handle_home_directory(t_env *env)
{
	char	*home;

	home = get_env_value(env, "HOME");
	if (!home)
	{
		cd_error("HOME not set");
		return (NULL);
	}
	return (home);
}

static char	*handle_oldpwd_directory(t_env *env)
{
	char	*oldpwd;

	oldpwd = get_env_value(env, "OLDPWD");
	if (!oldpwd)
	{
		cd_error("OLDPWD not set");
		return (NULL);
	}
	printf("%s\n", oldpwd);
	return (oldpwd);
}

char	*get_target_directory(t_cmd *cmd, t_env *env)
{
	if (!cmd->args[1])
		return (handle_home_directory(env));
	if (cmd->args[1][0] == '~' && cmd->args[1][1] == '\0')
		return (handle_home_directory(env));
	if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
		return (handle_oldpwd_directory(env));
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
