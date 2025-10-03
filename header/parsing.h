/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/03 12:55:57 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
	TOKEN_EOF
}						types_tokens;

typedef struct s_token
{
	types_tokens		type;
	char				*value;
	bool				single_quotes;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd
{
	char				**args;
	bool				*args_single_quotes;
	int					args_count;
	char				*input_file;
	bool				input_single_quotes;
	char				*output_file;
	bool				output_single_quotes;
	bool				append_mode;
	char				**heredoc_delims;
	bool				*heredoc_delim_quotes;
	int					heredoc_count;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_env_var
{
	char *name;  // Nom (ex: "PATH")
	char *value; // Valuer (ex : "/usr/bin:/bin")
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_exec_env
{
	char				**envp;
	t_env_var			*env_list;
	int					exit_status;
	int					stdin_backup;
	int					stdout_backup;
}						t_env;

/* ************************************************************************** */
/*                                PRE-CHECK                                   */
/* ************************************************************************** */

void					trim(char **str);
bool					pre_check(char **str);
bool					check_if_empty(char *str);
bool					check_quotes(char *str);
bool					check_pipes(char *str);
bool					check_forbidden_sequences(char *str);
bool					check_operators(char *str);

/* ************************************************************************** */
/*                              TOKENIZATION                                  */
/* ************************************************************************** */

t_token					*tokenization(char *str);
bool					is_operator(char c);
bool					is_quote(char c);
char					*extract_operator(char *str, int *i);
char					*extract_word(char *str, int *i);
char					*extract_quote(char *str, int *i,
							bool *is_single_quote);
t_token					*ft_lstnew_pars(void *content);
void					ft_lstadd_back_pars(t_token **lst, t_token *new);
types_tokens			define_type(char *str);

/* ************************************************************************** */
/*                              COMMANDS                                      */
/* ************************************************************************** */

void					add_arg(t_cmd *command, char *argument,
							bool is_single_quote, int position);
bool					redirection(t_cmd *command, types_tokens type,
							char *file, bool is_single_quote);
t_cmd					*parse_command(t_token **current);
t_cmd					*parser_tokens(t_token *list);
t_cmd					*init_new_command(void);
bool					is_redirection(t_token *token);
void					ft_lstadd_back_commands(t_cmd **lst, t_cmd *new);

/* ************************************************************************** */
/*                              EXPANSION                                     */
/* ************************************************************************** */

void					expansion(t_cmd *commands, t_env *env);
void					replace_in_command(t_cmd *commands, char *str, int i);
char					*extract_variable(char *str);
bool					is_variable(char *str);
char					*build_full_command(char *original, t_env *env);
char					*extract_chain(char *str, int start, int end);

/* ************************************************************************** */
/*                            UTILITY FUNCTIONS                               */
/* ************************************************************************** */

int						get_size_quote(char *str, int i);
char					*ft_strdup_pars(const char *s1);
size_t					ft_strlen_pars(const char *s);
size_t					ft_strlcpy_pars(char *dest, const char *src,
							size_t dstsize);
int						ft_strcmp_pars(const char *s1, const char *s2);
void					*ft_memcpy_pars(void *dest, const void *src, size_t n);
int						ft_strncmp_pars(const char *s1, const char *s2,
							size_t n);
char					*ft_itoa_pars(int n);

/* ************************************************************************** */
/*                           		MANIP ENV                                   */
/* ************************************************************************** */

t_env_var				*create_new_env_var(char *str);
char					*get_env_value(t_env *env, char *name);
void					set_env_var(t_env *env, char *name, char *value);
void					unset_env_var(t_env *env, char *name);
char					**env_list_to_array(t_env_var *list);
void					ft_lstdelone_pars(t_env_var *lst);
void					ft_lstclear_pars(t_env_var **lst);
int						ft_lstsize_pars(t_env_var *lst);
void					add_env_var(t_env_var **list, char *env_string);

/* ************************************************************************** */
/*                              SIGNALS                                       */
/* ************************************************************************** */

void					handle_sig_int_interactive(int signal);
void					handle_sig_int_command(int signal);
void					handle_sig_quit(int signal);
void					setup_signals_interactive(void);
void					restore_signal(void);
void					setup_signals_command(void);

/* ************************************************************************** */
/*                            FREE MEMORY                                     */
/* ************************************************************************** */

void					free_commands(t_cmd *commands);
void					free_tokens(t_token *tokens);

//===Main===

t_env					*init_env(char **envp);
int						execute_single_cmd(t_cmd *cmd, t_env *env);
int						execute_cmd_pipeline(t_cmd *cmd_list, t_env *env);

//===Builtin_simple===

int						builtin_exit(t_cmd *cmd, t_env *env);
int						builtin_pwd(t_cmd *cmd, t_env *env);
int						builtin_env(t_cmd *cmd, t_env *env);
int						builtin_echo(t_cmd *cmd, t_env *env);

//===Builtin_cd===
int						builtin_cd(t_cmd *cmd, t_env *env);
char					*get_target_directory(t_cmd *cmd, t_env *env);
void					update_pwd_variables(t_env *env, char *old_pwd);
//===Builtin_export===

char					*remove_quotes(char *str);
int						builtin_export(t_cmd *cmd, t_env *env);
int						export_process_args(t_cmd *cmd, t_env *env);
int						parse_export(char *str);
char					*extract_var(char *str);
char					*extract_value(char *str);
int						export_display_all(t_env *env);

//===Builtin_unset===

int						builtin_unset(t_cmd *cmd, t_env *env);
int						parse_unset(char *str);

//===Utils_builtin===

bool					is_builtin(char *cmd_name);
int						execute_builtin(t_cmd *cmd, t_env *env);
int						is_valid_number(char *str);
int						cd_error(char *msg);

//===Path===

char					*find_command_path(char *cmd_name, char **envp);
char					**get_paths(char **envp);
char					*join3(const char *a, const char *b, const char *c);
char					*build_candidate(const char *dir, const char *cmd);
const char				*find_path_value(char **envp);
int						count_segments(const char *s);
char					**fill_segments(const char *s, int count);
int						has_slash(const char *cmd);
int						calculate_total_length(const char *a, const char *b,
							const char *c);
char					*search_command_in_paths(const char *cmd, char **paths);
char					*try_command_with_slash(const char *cmd);
char					*create_segment(const char *s, int start, int len);
int						fill_single_segment(const char *s, char **tab, int i,
							int *start);
void					free_tab(char **tab);

//===Exec_external_cmd===

int						execute_external_command(t_cmd *cmd, t_env *env);
void					exec_child_process(char *path, t_cmd *cmd, t_env *env);

//===Pipes===

void					close_if_valid(int fd);
void					child_exec(t_cmd *cmd, t_env *env, int in_fd,
							int out_fd);
int						spawn(t_cmd *cmd, t_env *env, int last_in,
							int *next_in);
int						wait_all(pid_t *pids, int n);
int						execute_pipeline(t_cmd *cmd_list, t_env *env);

//==Heredoc===

int						process_heredoc(t_cmd *cmd, t_env *env);
void					setup_heredoc_signals(void);
void					handle_heredoc_sigint(int signal);
void					read_one_heredoc(int pipe_fd[2], char *delim,
							bool has_quotes, t_env *env);

//===single_exec===

void					apply_redirs(int in_fd, int out_fd);
void					restore_stdio(int saved_in, int saved_out);
int						run_builtin_parent(t_cmd *cmd, t_env *env);
int						run_external_child(t_cmd *cmd, t_env *env);
int						execute_single_cmd(t_cmd *cmd, t_env *env);

//===utils_pipes===

void					close_if_valid(int fd);
int						execute_cmd_pipeline(t_cmd *cmd_list, t_env *env);

//===Utils_redir===

int						open_in(const char *path, int *fd);
int						open_out_trunc(const char *path, int *fd);
int						open_out_append(const char *path, int *fd);
int						setup_redirections(t_cmd *cmd, t_env *env, int *in_fd,
							int *out_fd);

#endif