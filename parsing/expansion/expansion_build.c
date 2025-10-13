/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:05:23 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 15:38:44 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static void	append_env_value(char *variable, t_env *env, char *result,
		int *result_pos)
{
	char	*in_env;
	int		k;

	in_env = get_env_value(env, variable);
	if (in_env != NULL)
	{
		k = 0;
		while (in_env[k])
		{
			result[*result_pos] = in_env[k];
			(*result_pos)++;
			k++;
		}
	}
}

static size_t	handle_exit_status_var(size_t j, t_build_data *data)
{
	append_exit_status(data->env, data->result, data->result_pos);
	return (j + 1);
}

static size_t	handle_env_var(char *original, size_t i, size_t j,
		t_build_data *data)
{
	char	*variable;

	while (j < ft_strlen_pars(original) && ((original[j] >= 'a'
				&& original[j] <= 'z') || (original[j] >= 'A'
				&& original[j] <= 'Z') || (original[j] >= '0'
				&& original[j] <= '9') || original[j] == '_'))
		j++;
	variable = extract_chain(original, i + 1, j);
	append_env_value(variable, data->env, data->result, data->result_pos);
	free(variable);
	return (j);
}

static long long	eval_arithmetic(char *expr, t_env *env);

static size_t	handle_arithmetic_expansion(char *original, size_t i,
		t_build_data *data)
{
	size_t		j;
	char		*expr;
	long long	result;
	char		*result_str;
	int			k;

	j = i + 2;
	while (j < ft_strlen_pars(original) && !(original[j] == ')'
			&& original[j + 1] == ')'))
		j++;
	if (j >= ft_strlen_pars(original))
		return (i + 1);
	expr = extract_chain(original, i + 3, j);
	result = eval_arithmetic(expr, data->env);
	free(expr);
	result_str = ft_itoa(result);
	k = 0;
	while (result_str[k])
		data->result[(*data->result_pos)++] = result_str[k++];
	free(result_str);
	return (j + 2);
}

static size_t	process_dollar_sign(char *original, size_t i,
		t_build_data *data)
{
	size_t	j;

	j = i + 1;
	if (j < ft_strlen_pars(original) && original[j] == '?')
		return (handle_exit_status_var(j, data));
	else if (j + 1 < ft_strlen_pars(original) && original[j] == '('
		&& original[j + 1] == '(')
		return (handle_arithmetic_expansion(original, i, data));
	else if (j < ft_strlen_pars(original) && ((original[j] >= 'a'
				&& original[j] <= 'z') || (original[j] >= 'A'
				&& original[j] <= 'Z') || original[j] == '_'))
		return (handle_env_var(original, i, j, data));
	data->result[(*data->result_pos)++] = original[i];
	return (i + 1);
}

char	*build_full_command(char *original, t_env *env, size_t i,
		bool heredoc_mode)
{
	t_build_data	data;
	int				result_pos;
	char			current_quote;

	data.result = malloc(4096 * sizeof(char));
	if (!data.result)
		return (NULL);
	data.original = original;
	data.env = env;
	data.result_pos = &result_pos;
	result_pos = 0;
	current_quote = 0;
	while (i < ft_strlen_pars(original))
	{
		if (!heredoc_mode && (original[i] == '"' || original[i] == 39)
			&& (current_quote == 0 || original[i] == current_quote))
			handle_quote_state(original[i++], &current_quote, data.result,
				&result_pos);
		else if (original[i] == '$' && (heredoc_mode || current_quote != 39))
			i = process_dollar_sign(original, i, &data);
		else
			data.result[result_pos++] = original[i++];
	}
	data.result[result_pos] = '\0';
	return (data.result);
}

static char	*expand_vars_in_expr(char *expr, t_env *env)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;
	int		k;
	int		m;

	result = malloc(4096 * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	k = 0;
	while (expr[i])
	{
		if ((expr[i] >= 'A' && expr[i] <= 'Z') || (expr[i] >= 'a'
				&& expr[i] <= 'z') || expr[i] == '_')
		{
			j = i;
			while ((expr[j] >= 'A' && expr[j] <= 'Z') || (expr[j] >= 'a'
					&& expr[j] <= 'z') || (expr[j] >= '0' && expr[j] <= '9')
				|| expr[j] == '_')
				j++;
			var_name = extract_chain(expr, i, j);
			var_value = get_env_value(env, var_name);
			free(var_name);
			if (var_value)
			{
				m = 0;
				while (var_value[m])
					result[k++] = var_value[m++];
			}
			else
				result[k++] = '0';
			i = j;
		}
		else
			result[k++] = expr[i++];
	}
	result[k] = '\0';
	return (result);
}

static long long	parse_number(char *expr, int *idx, int is_first)
{
	long long	result;
	int			sign;

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

static long long	eval_simple(char *expr)
{
	long long	result;
	long long	num;
	char		op;
	int			i;

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
		if (op == '+')
			result += num;
		else if (op == '-')
			result -= num;
		else if (op == '*')
			result *= num;
		else if (op == '/' && num != 0)
			result /= num;
		else if (op == '%' && num != 0)
			result %= num;
	}
	return (result);
}

static long long	eval_arithmetic(char *expr, t_env *env)
{
	char		*expanded;
	long long	result;

	expanded = expand_vars_in_expr(expr, env);
	if (!expanded)
		return (0);
	result = eval_simple(expanded);
	free(expanded);
	return (result);
}
