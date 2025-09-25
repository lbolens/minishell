/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:30:03 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 10:56:25 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

/* int		main(int argc, char **argv, char **envp)
{
	t_env *env;
	
	init_env(envp);
	if (is_builtin(cmd->args[0]))
		execute_builtin(cmd, env);
	else
		execute_external_command(cmd, env)
} */

int main(int argc, char **argv, char **envp)
{
    t_env *env;
    char *path;
    
    // Initialiser ton environnement
    env = init_env(envp);
    if (!env)
        return (1);
    
    // Tester quelques commandes
    printf("=== TEST PATH RESOLUTION ===\n");
    
    path = find_command_path("ls", env->envp);
    printf("ls -> %s\n", path ? path : "NOT FOUND");
    if (path) free(path);
    
    path = find_command_path("cat", env->envp);
    printf("cat -> %s\n", path ? path : "NOT FOUND");
    if (path) free(path);
    
    path = find_command_path("/bin/echo", env->envp);  // Chemin absolu
    printf("/bin/echo -> %s\n", path ? path : "NOT FOUND");
    if (path) free(path);
    
    path = find_command_path("commande_inexistante", env->envp);
    printf("commande_inexistante -> %s\n", path ? path : "NOT FOUND");
    if (path) free(path);
    
    // Test avec PATH vide
    printf("\n=== TEST SANS PATH ===\n");
    path = find_command_path("ls", NULL);
    printf("ls (sans envp) -> %s\n", path ? path : "NOT FOUND");
    
    free_exec_env(env);
    return (0);
}