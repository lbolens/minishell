/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/23 16:00:00 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

/* ************************************************************************** */
/*                                LISTS                                      */
/* ************************************************************************** */

t_token				*ft_lstnew(void *content);
void				ft_lstadd_back(t_token **lst, t_token *new);
types_tokens		define_type(char *str);

/* ************************************************************************** */
/*                            UTILITY FUNCTIONS                              */
/* ************************************************************************** */

int					get_size_quote(char *str, int i);
char				*ft_strdup(const char *s1);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);
int					ft_strcmp(const char *s1, const char *s2);

#endif