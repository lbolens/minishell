/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:30:03 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 11:47:02 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../header/parsing.h"

/* int		main(int argc, char **argv, char **envp)
{
	t_env *env;
	
	init_env(envp);
	if (is_builtin(cmd->args[0]))
		execute_builtin(cmd, env);
	else
		execute_external_command(cmd, env)
} */
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

char *find_command_path(char *cmd_name, char **envp);

int main(void)
{
    extern char **environ;
    char *path;
    
    printf("=== TEST PATH RESOLUTION ===\n");
    
    path = find_command_path("ls", environ);
    printf("ls -> %s\n", path ? path : "NOT FOUND");
    if (path) 
        free(path);
    
    return (0);
}