/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:13:31 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 11:04:01 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H



typedef struct s_exec_env
{
	char	**envp;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}			t_env;

typedef struct s_cmd
{
	char			**args;
	char			*input_file;
	char			*output_file;
	bool			append_mode;
	char			*heredoc_delim;
	struct s_cmd	*next;
}					t_cmd;


//===Main===

t_env		*init_env(char **envp);

//===Builtin_simple===

int			execute_builtin(t_cmd *cmd, t_env *env);
t_env		*init_env(char **envp);
bool		is_builtin(char *cmd_name);
int			is_valid_number(char *str);
int			cd_error(char *msg);

//===Builtin_cd===

void		update_env_variable(t_env *env, char *name, char *value);

//===Builtin_export===

int			parse_export(char *str);
char		*extract_var(char *str);
int			export_display_all(t_env *env);
int			export_process_args(t_cmd *cmd, t_env *env);

//===Builtin_unset===

void		remove_env_variable(t_env *env, char *arg);

//===Path===

char		*find_command_path(char *cmd_name, char **envp);
char		**get_paths(char **envp);
char		*join3(const char *a, const char *b, const char *c);
char		*build_candidate(const char *dir, const char *cmd);
const char	*find_path_value(char **envp);
int			count_segments(const char *s);
char		**fill_segments(const char *s, int count);
int			has_slash(const char *cmd);
int			calculate_total_length(const char *a, const char *b, const char *c);
char		*search_command_in_paths(const char *cmd, char **paths);
char		*try_command_with_slash(const char *cmd);
char		*create_segment(const char *s, int start, int len);
int			fill_single_segment(const char *s, char **tab, int i, int *start);
void		free_tab(char **tab);

#endif