/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:54:43 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 11:11:35 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	builtin_cd(t_cmd *cmd, t_env *env)
{
	char	*current_pwd;
	char	*target_dir;

	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (cd_error("getcwd"));
	target_dir = get_target_directory(cmd);
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

char	*get_target_directory(t_cmd *cmd)
{
	char	*home;
	char	*oldpwd;

	if (!cmd->args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			cd_error("HOME not set");
			return (NULL);
		}
		return (home);
	}
	if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		oldpwd = getenv("OLDPWD");
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

	update_env_variable(env, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env_variable(env, "PWD", new_pwd);
		free(new_pwd);
	}
}

void	update_env_variable(t_env *env, char *name, char *value)
{
	int		i;
	char	*new_var;
	int		name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], name, name_len) == 0
			&& env->envp[i][name_len] == '=')
		{
			free(env->envp[i]);
			env->envp[i] = create_env_string(name, value);
			return ;
		}
		i++;
	}
}

char	*create_env_string(char *name, char *value)
{
	char	*result;
	int		len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	result = malloc(len);
	if (!result)
		return (NULL);
	ft_strcpy(result, name);
	ft_strcat(result, "=");
	ft_strcat(result, value);
	return (result);
}
