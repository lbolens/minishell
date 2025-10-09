/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:30:03 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/09 10:58:40 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

static void	rebuild_envp_from_list(t_env *env)
{
	if (!env)
		return ;
	if (env->envp)
		free_tab(env->envp);
	env->envp = env_list_to_array(env->env_list);
}

static void	execute_parsed_command(t_cmd *cmd, t_env *env)
{
	expansion(cmd, env);
	quote_removal(cmd);
	rebuild_envp_from_list(env);
	setup_signals_command();
	env->exit_status = execute_cmd_pipeline(cmd, env);
	setup_signals_interactive();
	free_commands(cmd);
}

static void	process_tokens(t_token *token, t_env *env)
{
	t_cmd	*cmd;

	if (!token)
		return ;
	cmd = parser_tokens(token);
	if (cmd)
		execute_parsed_command(cmd, env);
	free_tokens(token);
}

static void	process_input(char *input, t_env *env)
{
	t_token	*token;

	if (input[0] != '\0' && input[0] != ' ')
		add_history(input);
	if (ft_strlen(input) == 0)
		return ;
	if (pre_check(&input))
	{
		token = tokenization(input);
		process_tokens(token, env);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
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
			printf("exit\n");
			break ;
		}
		process_input(input, env);
		free(input);
	}
	free_tab(env->envp);
	ft_lstclear_pars(&env->env_list);
	free(env);
	return (0);
}
