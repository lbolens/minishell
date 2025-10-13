/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_arithmetic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:31:24 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/13 13:54:18 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static void	write_result_to_buffer(long result, t_build_data *data)
{
	char	*result_str;
	int		k;

	result_str = ft_itoa(result);
	k = 0;
	while (result_str[k])
		data->result[(*data->result_pos)++] = result_str[k++];
	free(result_str);
}

static int	is_not_double_close(char *str, size_t j, size_t len)
{
	if (j >= len)
		return (0);
	if (str[j] == ')' && str[j + 1] == ')')
		return (0);
	return (1);
}

size_t	handle_arithmetic_expansion(char *original, size_t i,
		t_build_data *data)
{
	size_t		j;
	char		*expr;
	long long	result;
	size_t		len;

	j = i + 2;
	len = ft_strlen_pars(original);
	while (j < len && is_not_double_close(original, j, len))
		j++;
	if (j >= len)
		return (i + 1);
	expr = extract_chain(original, i + 3, j);
	result = eval_arithmetic(expr, data->env);
	free(expr);
	write_result_to_buffer(result, data);
	return (j + 2);
}

long	eval_arithmetic(char *expr, t_env *env)
{
	char	*expanded;
	long	result;

	expanded = expand_vars_in_expr(expr, env);
	if (!expanded)
		return (0);
	result = eval_simple(expanded);
	free(expanded);
	return (result);
}
