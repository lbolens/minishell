/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:13:31 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/23 16:05:41 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "../parsing/minishell.h"

typedef struct s_exec_env {
    char **envp;
    int exit_status;
    int stdin_backup;
    int stdout_backup;
} t_exec_env;


//===Main===

t_exec_env	*init_exec_env(char **envp);

#endif