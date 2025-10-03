/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:30:03 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/03 10:42:38 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

/* int	execute_cmd_pipeline(t_cmd *cmd_list, t_env *env)
{
	t_cmd	*current;
	int		exit_code;

	exit_code = 0;
	if (!cmd_list)
		return (1);
	current = cmd_list;
	while (current)
	{
		if (!current->next)
		{
			exit_code = execute_single_cmd(current, env);
		}
		else
		{
			exit_code = execute_pipeline(cmd_list, env); // a coder
			break ;
		} 
		current = current->next;
	}
	return (exit_code);
} */

static void	rebuild_envp_from_list(t_env *env)
{
	if (!env)
		return ;
	if (env->envp)
		free_tab(env->envp);
	env->envp = env_list_to_array(env->env_list);
}

/* int	execute_single_cmd(t_cmd *cmd, t_env *env)
{
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd, env));
	else
		return (execute_external_command(cmd, env));
} */

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_token	*token;
	t_cmd	*cmd;
	char	*input;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
		return (1);
	setup_signals_interactive();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n"); // ctrl-d
			break ;
		}
		if (input[0] != '\0' && input[0] != ' ')
			add_history(input);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		if (pre_check(&input))
		{
			token = tokenization(input);
			if (token)
			{
				cmd = parser_tokens(token);
				if (cmd)
				{
					// Maintenant expansion doit utiliser la liste chaînée
					expansion(cmd, env);
					rebuild_envp_from_list(env);
					setup_signals_command();
					env->exit_status = execute_cmd_pipeline(cmd, env);
					setup_signals_interactive();
					free_commands(cmd);
				}
				free_tokens(token);
			}
		}
		free(input);
	}
	free_tab(env->envp); 
	ft_lstclear_pars(&env->env_list);
	free(env);
	return (0);
}
