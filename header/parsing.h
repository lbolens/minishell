/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/14 16:44:44 by lbolens          ###   ########.fr       */
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

/* ************************************************************************** */
/*                              STRUCTURES                                    */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
	TOKEN_EOF
}						t_types_tokens;

typedef struct s_token
{
	t_types_tokens		type;
	char				*value;
	bool				single_quotes;
	bool				double_quotes;
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
	char				**all_output_files;
	bool				*all_output_append;
	int					output_count;
	char				**heredoc_delims;
	bool				*heredoc_delim_quotes;
	bool				*heredoc_delim_double_quotes;
	int					heredoc_count;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_exec_env
{
	char				**envp;
	t_env_var			*env_list;
	int					exit_status;
	int					stdin_backup;
	int					stdout_backup;
	void				*current_tokens;
	void				*current_cmd;
	char				*current_input;
}						t_env;

typedef struct s_build_data
{
	char				*original;
	char				*result;
	int					*result_pos;
	t_env				*env;
}						t_build_data;

typedef struct s_expand_buf
{
	char				*result;
	int					k;
	int					i;
}						t_expand_buf;

typedef struct s_exec_ctx
{
	t_cmd				*cmd;
	t_env				*env;
	int					in_fd;
	int					out_fd;
}						t_exec_ctx;

typedef struct s_quote_flags
{
	int					len;
	bool				is_single;
	bool				is_double;
}						t_quote_flags;

typedef struct s_extract_data
{
	int					start;
	int					len;
	int					j;
	char				*word;
	t_quote_flags		flags;
}						t_extract_data;

typedef struct s_redir_info
{
	t_types_tokens		type;
	char				*file;
	bool				is_single_quote;
	bool				is_double_quote;
}						t_redir_info;

typedef struct s_heredoc_arrays
{
	char				**new_delims;
	bool				*new_quotes;
	bool				*new_double_quotes;
}						t_heredoc_arrays;

/* ************************************************************************** */
/*                              MAIN & INIT                                   */
/* ************************************************************************** */

t_env					*init_env(char **envp);
void					cleanup_env(t_env *env);

/* ************************************************************************** */
/*                              PRE-CHECK                                     */
/* ************************************************************************** */

void					trim(char **str, size_t len);
bool					pre_check(char **str);
bool					check_if_empty(char *str);
bool					check_quotes(char *str);
bool					check_pipes(char *str, int i);
bool					check_forbidden_sequences(char *str);
bool					check_operators(char *str, int i);

/* ************************************************************************** */
/*                              TOKENIZATION                                  */
/* ************************************************************************** */

t_token					*tokenization(char *str);
bool					is_operator(char c);
char					*extract_operator(char *str, int *i);
char					*extract_word(char *str, int *i, bool *is_single,
							bool *is_double);
t_token					*ft_lstnew_pars(void *content);
void					ft_lstadd_back_pars(t_token **lst, t_token *new);
t_types_tokens			define_type(char *str);

/* ************************************************************************** */
/*                              PARSING                                       */
/* ************************************************************************** */

t_cmd					*parser_tokens(t_token *list);
t_cmd					*parse_command(t_token **current);
t_cmd					*init_new_command(void);
void					add_arg(t_cmd *command, char *argument,
							bool is_single_quote, int position);
bool					redirection(t_cmd *command, t_redir_info *info);
bool					is_redirection(t_token *token);
void					ft_lstadd_back_commands(t_cmd **lst, t_cmd *new);
bool					handle_input_redir(t_cmd *command, char *file,
							bool is_single_quote);
int						is_append_mode(char *str);
bool					handle_heredoc_redir(t_cmd *command,
							t_redir_info *info);

/* ************************************************************************** */
/*                              EXPANSION                                     */
/* ************************************************************************** */

void					expansion(t_cmd *commands, t_env *env);
void					quote_removal(t_cmd *commands);
char					*remove_quotes_from_string(char *str);
void					remove_quotes_from_args(t_cmd *commands);
void					remove_quotes_from_input(t_cmd *commands);
void					remove_quotes_from_outputs(t_cmd *commands);
char					*build_full_command(char *original, t_env *env,
							size_t i, bool heredoc_mode);
void					replace_in_command(t_cmd *commands, char *str, int i);
char					*extract_variable(char *str);
char					*extract_chain(char *str, int start, int end);
bool					is_variable(char *str);
void					handle_quote_state(char c, char *current_quote,
							char *result, int *result_pos);
char					*expand_vars_in_expr(char *expr, t_env *env);
long					eval_arithmetic(char *expr, t_env *env);
long					eval_simple(char *expr);
long					parse_number(char *expr, int *idx, int is_first);
size_t					handle_arithmetic_expansion(char *original, size_t i,
							t_build_data *data);
void					append_env_value(char *variable, t_env *env,
							char *result, int *result_pos);
size_t					handle_exit_status_var(size_t j, t_build_data *data);
size_t					handle_env_var(char *original, size_t i, size_t j,
							t_build_data *data);
size_t					process_dollar_sign(char *original, size_t i,
							t_build_data *data);

/* ************************************************************************** */
/*                              ENVIRONMENT                                   */
/* ************************************************************************** */

t_env_var				*create_new_env_var(char *str);
void					add_env_var(t_env_var **list, char *env_string);
char					*get_env_value(t_env *env, char *name);
void					set_env_var(t_env *env, char *name, char *value);
void					unset_env_var(t_env *env, char *name);
char					**env_list_to_array(t_env_var *list);
int						ft_lstsize_pars(t_env_var *lst);
void					ft_lstdelone_pars(t_env_var *lst);
void					ft_lstclear_pars(t_env_var **lst);
char					*extract_name(char *str);
char					*extract_env_value(char *str);
void					append_exit_status(t_env *env, char *result,
							int *result_pos);

/* ************************************************************************** */
/*                              BUILTINS                                      */
/* ************************************************************************** */

bool					is_builtin(char *cmd_name);
int						execute_builtin(t_cmd *cmd, t_env *env);
int						builtin_echo(t_cmd *cmd, t_env *env);
int						builtin_cd(t_cmd *cmd, t_env *env);
int						builtin_pwd(t_cmd *cmd, t_env *env);
int						builtin_export(t_cmd *cmd, t_env *env);
int						builtin_unset(t_cmd *cmd, t_env *env);
int						builtin_env(t_cmd *cmd, t_env *env);
int						builtin_exit(t_cmd *cmd, t_env *env);
char					*handle_home_directory(t_env *env);
char					*handle_oldpwd_directory(t_env *env);
char					*resolve_parent_dir(char *pwd);
int						process_single_export(char *arg, t_env *env);

/* ************************************************************************** */
/*                          BUILTINS HELPERS                                  */
/* ************************************************************************** */

char					*get_target_directory(t_cmd *cmd, t_env *env);
void					update_pwd_variables(t_env *env, char *old_pwd,
							char *target_dir);
int						cd_error(char *msg);
char					*remove_quotes(char *str);
int						export_display_all(t_env *env);
int						export_process_args(t_cmd *cmd, t_env *env);
int						parse_export(char *str);
int						parse_unset(char *str);
char					*extract_var(char *str);
char					*extract_value(char *str);
int						is_valid_number(char *str);

/* ************************************************************************** */
/*                              PATH RESOLUTION                               */
/* ************************************************************************** */

char					*find_command_path(char *cmd_name, char **envp);
char					**get_paths(char **envp);
const char				*find_path_value(char **envp);
char					*search_command_in_paths(const char *cmd, char **paths);
char					*try_command_with_slash(const char *cmd);
char					*build_candidate(const char *dir, const char *cmd);
char					*join3(const char *a, const char *b, const char *c);
int						has_slash(const char *cmd);
int						count_segments(const char *s);
char					**fill_segments(const char *s, int count);
char					*create_segment(const char *s, int start, int len);
int						fill_single_segment(const char *s, char **tab, int i,
							int *start);
int						calculate_total_length(const char *a, const char *b,
							const char *c);

/* ************************************************************************** */
/*                              EXECUTION                                     */
/* ************************************************************************** */

int						execute_cmd_pipeline(t_cmd *cmd_list, t_env *env);
int						execute_single_cmd(t_cmd *cmd, t_env *env);
int						execute_external_command(t_cmd *cmd, t_env *env);
int						execute_pipeline(t_cmd *cmd_list, t_env *env);
void					exec_child_process(char *path, t_cmd *cmd, t_env *env);

/* ************************************************************************** */
/*                              PIPES                                         */
/* ************************************************************************** */

int						spawn(t_cmd *cmd, t_env *env, int last_in,
							int *next_in);
void					child_exec(t_cmd *cmd, t_env *env, int in_fd,
							int out_fd);
int						wait_all(pid_t *pids, int n);
void					close_if_valid(int fd);
void					cleanup_fds(int in_fd, int out_fd, int last_in,
							int pipe_w);
void					adjust_fds(int *in_fd, int *out_fd, int last_in,
							int *p);

/* ************************************************************************** */
/*                              REDIRECTIONS                                  */
/* ************************************************************************** */

int						setup_redirections(t_cmd *cmd, t_env *env, int *in_fd,
							int *out_fd);
int						setup_output_redir(t_cmd *cmd, int *out_fd);
int						open_in(const char *path, int *fd);
int						open_out_trunc(const char *path, int *fd);
int						open_out_append(const char *path, int *fd);
void					apply_redirs(int in_fd, int out_fd);
void					restore_stdio(int saved_in, int saved_out);

/* ************************************************************************** */
/*                              HEREDOC                                       */
/* ************************************************************************** */

int						process_heredoc(t_cmd *cmd, t_env *env);
void					read_one_heredoc(int pipe_fd[2], char *delim,
							bool has_quotes, t_env *env);
void					setup_heredoc_signals(void);
void					handle_heredoc_sigint(int signal);

/* ************************************************************************** */
/*                              SIGNALS                                       */
/* ************************************************************************** */

void					setup_signals_interactive(void);
void					setup_signals_command(void);
void					restore_signal(void);
void					handle_sig_int_interactive(int signal);
// void					handle_sig_int_command(int signal);
// void					handle_sig_quit(int signal);

/* ************************************************************************** */
/*                              SINGLE COMMAND                                */
/* ************************************************************************** */

int						run_builtin_parent(t_cmd *cmd, t_env *env);
int						run_external_child(t_cmd *cmd, t_env *env);

/* ************************************************************************** */
/*                              UTILITY FUNCTIONS                             */
/* ************************************************************************** */

int						get_size_quote(char *str, int i);
char					*ft_strdup_pars(const char *s1);
size_t					ft_strlen_pars(const char *s);
size_t					ft_strlcpy_pars(char *dest, const char *src,
							size_t dstsize);
int						ft_strcmp_pars(const char *s1, const char *s2);
int						ft_strncmp_pars(const char *s1, const char *s2,
							size_t n);
void					*ft_memcpy_pars(void *dest, const void *src, size_t n);
char					*ft_itoa_pars(int n);
void					free_tab(char **tab);

/* ************************************************************************** */
/*                              FREE MEMORY                                   */
/* ************************************************************************** */

void					free_commands(t_cmd *commands);
void					free_tokens(t_token *tokens);
void					free_args(t_cmd *cmd);
void					free_output_files(t_cmd *cmd);
void					free_heredoc_delims(t_cmd *cmd);
void					free_single_command(t_cmd *cmd);

#endif