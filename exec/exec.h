/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:13:31 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/24 16:28:54 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include "../parsing/parsing.h"
# include <stdbool.h>

typedef struct s_exec_env
{
	char	**envp;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}			t_env;

//===Main===

t_env	*init_env(char **envp);

//===Builtin_simple===

int			execute_builtin(t_cmd *cmd, t_env *env);
t_env	*init_exec_env(char **envp);
bool		is_builtin(char *cmd_name);
int			is_valid_number(char *str);
int			cd_error(char *msg);

//===Builtin_cd===

void		update_env_variable(t_env *env, char *name, char *value);

//===Builtin_export===

int			parse_export(char *str);
char		*extract_var(char *str);

#endif