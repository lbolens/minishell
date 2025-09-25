/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/25 14:10:19 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
}					types_tokens;

typedef struct s_token
{
	types_tokens	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	char			**args;
	char			*input_file;
	char			*output_file;
	bool			append_mode;
	char			*heredoc_delim;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_exec_env
{
	char			**envp;
	int				exit_status;
	int				stdin_backup;
	int				stdout_backup;
}					t_env;

/* ************************************************************************** */
/*                                PRE-CHECK                                   */
/* ************************************************************************** */

void				trim(char **str);
bool				pre_check(char **str);
bool				check_if_empty(char *str);
bool				check_quotes(char *str);
bool				check_pipes(char *str);
bool				check_forbidden_sequences(char *str);
bool				check_operators(char *str);

/* ************************************************************************** */
/*                              TOKENIZATION                                 */
/* ************************************************************************** */

t_token				*tokenization(char *str);
bool				is_operator(char c);
bool				is_quote(char c);
char				*extract_operator(char *str, int *i);
char				*extract_word(char *str, int *i);
char				*extract_quote(char *str, int *i);
t_token				*ft_lstnew_pars(void *content);
void				ft_lstadd_back_pars(t_token **lst, t_token *new);
types_tokens		define_type(char *str);

/* ************************************************************************** */
/*                              COMMANDS                                      */
/* ************************************************************************** */

void				add_arg(t_cmd *command, char *argument, int position);
bool				redirection(t_cmd *command, types_tokens type, char *file);
t_cmd				*parse_command(t_token **current);
t_cmd				*parser_tokens(t_token *list);
t_cmd				*init_new_command(void);
bool				is_redirection(t_token *token);
void				ft_lstadd_back_commands(t_cmd **lst, t_cmd *new);

/* ************************************************************************** */
/*                              EXPANSION                                     */
/* ************************************************************************** */

void				expansion(t_cmd *commands, char **env);
void				replace_in_command(t_cmd *commands, char *str, int i);
char				*extract_variable(char *str);
char				*check_in_env(char *str, char **env);
char				*extract_in_env(char *str);
bool				is_variable(char *str);

/* ************************************************************************** */
/*                            UTILITY FUNCTIONS                              */
/* ************************************************************************** */

int					get_size_quote(char *str, int i);
char				*ft_strdup_pars(const char *s1);
size_t				ft_strlen_pars(const char *s);
size_t				ft_strlcpy_pars(char *dest, const char *src,
						size_t dstsize);
int					ft_strcmp_pars(const char *s1, const char *s2);
void				*ft_memcpy_pars(void *dest, const void *src, size_t n);
int					ft_strncmp_pars(const char *s1, const char *s2, size_t n);

//===Main===

t_env				*init_env(char **envp);

//===Builtin_simple===

int					builtin_exit(t_cmd *cmd, t_env *env);
int					builtin_pwd(t_cmd *cmd, t_env *env);
int					builtin_env(t_cmd *cmd, t_env *env);
int					builtin_echo(t_cmd *cmd, t_env *env);
int					execute_builtin(t_cmd *cmd, t_env *env);
t_env				*init_env(char **envp);
bool				is_builtin(char *cmd_name);
int					is_valid_number(char *str);
int					cd_error(char *msg);

//===Builtin_cd===
int					builtin_cd(t_cmd *cmd, t_env *env);
char				*get_target_directory(t_cmd *cmd);
void				update_pwd_variables(t_env *env, char *old_pwd);
void				update_env_variable(t_env *env, char *name, char *value);
char				*create_env_string(char *name, char *value);

//===Builtin_export===

int					builtin_export(t_cmd *cmd, t_env *env);
int					export_process_args(t_cmd *cmd, t_env *env);
int					parse_export(char *str);
char				*extract_var(char *str);
char				*extract_value(char *str);
int					export_display_all(t_env *env);
int					export_process_args(t_cmd *cmd, t_env *env);

//===Builtin_unset===

int					builtin_unset(t_cmd *cmd, t_env *env);
void				remove_env_variable(t_env *env, char *arg);
int					parse_unset(char *str);

//===Utils_builtin===

bool				is_builtin(char *cmd_name);
int					execute_builtin(t_cmd *cmd, t_env *env);
int					is_valid_number(char *str);
int					cd_error(char *msg);

//===Path===

char				*find_command_path(char *cmd_name, char **envp);
char				**get_paths(char **envp);
char				*join3(const char *a, const char *b, const char *c);
char				*build_candidate(const char *dir, const char *cmd);
const char			*find_path_value(char **envp);
int					count_segments(const char *s);
char				**fill_segments(const char *s, int count);
int					has_slash(const char *cmd);
int					calculate_total_length(const char *a, const char *b,
						const char *c);
char				*search_command_in_paths(const char *cmd, char **paths);
char				*try_command_with_slash(const char *cmd);
char				*create_segment(const char *s, int start, int len);
int					fill_single_segment(const char *s, char **tab, int i,
						int *start);
void				free_tab(char **tab);

#endif