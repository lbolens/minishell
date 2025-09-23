/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:15:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/22 12:41:42 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include "libft/libft.h"

void    trim(char **str);
bool    pre_check(char *str);
bool    check_if_empty(char *str);
bool    check_quotes(char *str);
bool    check_pipes(char *str);
bool    check_forbidden_sequences(char *str);
bool    check_operators(char *str);

#endif