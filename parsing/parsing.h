/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/24 10:42:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
t_token				*ft_lstnew(void *content);
void				ft_lstadd_back(t_token **lst, t_token *new);
types_tokens		define_type(char *str);

/* ************************************************************************** */
/*                              COMMANDS                                      */
/* ************************************************************************** */

void				add_arg(t_cmd *command, char *argument, int position);
void				redirection(t_cmd *command, types_tokens type, char *file);
t_cmd				*parse_command(t_token **current);
t_cmd				*parser_tokens(t_token *list);
t_cmd				*init_new_command(void);
bool				is_redirection(t_token *token);
void				ft_lstadd_back_commands(t_cmd **lst, t_cmd *new);

/* ************************************************************************** */
/*                            UTILITY FUNCTIONS                              */
/* ************************************************************************** */

int					get_size_quote(char *str, int i);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);
int					ft_strcmp(const char *s1, const char *s2);
void				*ft_memcpy(void *dest, const void *src, size_t n);

#endif