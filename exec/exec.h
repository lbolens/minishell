/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:13:31 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/23 19:18:17 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include "../parsing/minishell.h"
# include <stdbool.h>

typedef struct s_exec_env
{
	char	**envp;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}			t_exec_env;

//===Main===

t_exec_env	*init_exec_env(char **envp);

//===Builtin===

int			execute_builtin(t_cmd *cmd, t_exec_env *env);
t_exec_env	*init_exec_env(char **envp);
bool		is_builtin(char *cmd_name);
int			is_valid_number(char *str);
int			cd_error(char *msg);

#endif