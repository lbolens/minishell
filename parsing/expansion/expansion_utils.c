/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:22:03 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:11:40 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_quote_state(char c, char *current_quote, char *result,
		int *result_pos)
{
	if (c == '"' && *current_quote == 0)
		*current_quote = '"';
	else if (c == 39 && *current_quote == 0)
		*current_quote = 39;
	else if (c == *current_quote)
		*current_quote = 0;
	result[(*result_pos)++] = c;
}

void	append_exit_status(t_env *env, char *result, int *result_pos)
{
	char	*status_str;
	int		k;

	status_str = ft_itoa_pars(env->exit_status);
	k = 0;
	while (status_str[k])
	{
		result[*result_pos] = status_str[k];
		(*result_pos)++;
		k++;
	}
	free(status_str);
}

static void	apply_operator(long *result, char op, long num)
{
	if (op == '+')
		*result += num;
	else if (op == '-')
		*result -= num;
	else if (op == '*')
		*result *= num;
	else if (op == '/' && num != 0)
		*result /= num;
	else if (op == '%' && num != 0)
		*result %= num;
}

long	eval_simple(char *expr)
{
	long	result;
	long	num;
	char	op;
	int		i;

	i = 0;
	result = parse_number(expr, &i, 1);
	while (expr[i])
	{
		while (expr[i] == ' ')
			i++;
		if (!expr[i])
			break ;
		op = expr[i++];
		num = parse_number(expr, &i, 0);
		apply_operator(&result, op, num);
	}
	return (result);
}

long	parse_number(char *expr, int *idx, int is_first)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (expr[*idx] == ' ')
		(*idx)++;
	if (is_first && (expr[*idx] == '-' || expr[*idx] == '+'))
	{
		if (expr[*idx] == '-')
			sign = -1;
		(*idx)++;
	}
	while (expr[*idx] >= '0' && expr[*idx] <= '9')
	{
		result = result * 10 + (expr[*idx] - '0');
		(*idx)++;
	}
	return (result * sign);
}
