/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:30:03 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/15 11:10:49 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	env->current_cmd = cmd;
	expansion(cmd, env);
	quote_removal(cmd);
	rebuild_envp_from_list(env);
	setup_signals_command();
	env->exit_status = execute_cmd_pipeline(cmd, env);
	setup_signals_interactive();
	free_commands(cmd);
	env->current_cmd = NULL;
}

static void	process_tokens(t_token *token, t_env *env)
{
	t_cmd	*cmd;

	if (!token)
		return ;
	env->current_tokens = token;
	cmd = parser_tokens(token);
	if (cmd)
		execute_parsed_command(cmd, env);
	free_tokens(token);
	env->current_tokens = NULL;
}

static void	process_input(char **input, t_env *env)
{
	t_token	*token;

	if ((*input)[0] != '\0' && (*input)[0] != ' ')
		add_history(*input);
	if (ft_strlen(*input) == 0)
		return ;
	if (pre_check(input))
	{
		env->current_input = *input;
		token = tokenization(*input);
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
		process_input(&input, env);
		free(input);
		env->current_input = NULL;
	}
	cleanup_env(env);
	return (0);
}
