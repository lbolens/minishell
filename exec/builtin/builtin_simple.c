/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:06:38 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/09 11:01:17 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

int	builtin_exit(t_cmd *cmd, t_env *env)
{
	int	exit_code;

	if (!cmd->args[1])
		exit_code = env->exit_status;
	else if (is_valid_number(cmd->args[1]))
		exit_code = ft_atoi(cmd->args[1]);
	else
	{
		printf("exit : %s: numeric argument required\n", cmd->args[1]);
		exit_code = 2;
	}
	printf("exit\n");
	exit(exit_code);
	return (0);
}

int	builtin_pwd(t_cmd *cmd, t_env *env)
{
	char	*pwd;

	(void)cmd;
	(void)env;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	builtin_env(t_cmd *cmd, t_env *env)
{
	t_env_var	*current;

	(void)cmd;
	current = env->env_list;
	while (current)
	{
		if (current->value && current->value[0] != '\0')
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}

static bool	is_n_flag(char *str)
{
	int	j;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	j = 1;
	while (str[j])
	{
		if (str[j] != 'n')
			return (false);
		j++;
	}
	return (true);
}

int	builtin_echo(t_cmd *cmd, t_env *env)
{
	int		i;
	bool	newline;

	(void)env;
	if (!cmd || !cmd->args)
		return (1);
	i = 1;
	newline = true;
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
	{
		newline = false;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
