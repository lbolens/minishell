/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:12:24 by hlongin           #+#    #+#             */
/*   Updated: 2025/10/09 11:19:12 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

int	wait_all(pid_t *pids, int n)
{
	int	i;
	int	wst;
	int	status;

	i = 0;
	status = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &wst, 0) > 0 && i == n - 1)
		{
			if (WIFEXITED(wst))
				status = WEXITSTATUS(wst);
			else if (WIFSIGNALED(wst))
				status = 128 + WTERMSIG(wst);
		}
		i++;
	}
	return (status);
}

static int	count_commands(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*cur;

	count = 0;
	cur = cmd_list;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

static int	execute_all_commands(t_cmd *cmd_list, t_env *env, pid_t *pids,
		int count)
{
	int		i;
	int		last_in;
	int		next_in;
	t_cmd	*cur;

	(void)count;
	i = 0;
	last_in = -1;
	cur = cmd_list;
	while (cur)
	{
		pids[i] = spawn(cur, env, last_in, &next_in);
		if (pids[i] == -1)
			return (0);
		last_in = next_in;
		cur = cur->next;
		i++;
	}
	return (1);
}

int	execute_pipeline(t_cmd *cmd_list, t_env *env)
{
	int		count;
	int		result;
	pid_t	*pids;

	if (!cmd_list || !cmd_list->next)
		return (execute_single_cmd(cmd_list, env));
	count = count_commands(cmd_list);
	pids = (pid_t *)malloc(sizeof(pid_t) * count);
	if (!pids)
		return (1);
	if (!execute_all_commands(cmd_list, env, pids, count))
	{
		free(pids);
		return (1);
	}
	result = wait_all(pids, count);
	free(pids);
	return (result);
}
