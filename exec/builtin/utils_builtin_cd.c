/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 09:22:47 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/10 09:23:17 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

char	*handle_home_directory(t_env *env)
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

char	*handle_oldpwd_directory(t_env *env)
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

char	*resolve_parent_dir(char *pwd)
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
