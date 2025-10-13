/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:31:45 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/13 13:36:51 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

static int	is_var_char_start(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

static int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_')
		return (1);
	return (0);
}

static void	copy_var_value(t_expand_buf *buf, char *var_value)
{
	int	m;

	if (var_value)
	{
		m = 0;
		while (var_value[m])
			buf->result[buf->k++] = var_value[m++];
	}
	else
		buf->result[buf->k++] = '0';
}

static int	extract_and_expand_var(char *expr, int i, t_env *env,
		t_expand_buf *buf)
{
	int		j;
	char	*var_name;
	char	*var_value;

	j = i;
	while (is_var_char(expr[j]))
		j++;
	var_name = extract_chain(expr, i, j);
	var_value = get_env_value(env, var_name);
	free(var_name);
	copy_var_value(buf, var_value);
	return (j);
}

char	*expand_vars_in_expr(char *expr, t_env *env)
{
	t_expand_buf	buf;

	buf.result = malloc(4096 * sizeof(char));
	if (!buf.result)
		return (NULL);
	buf.k = 0;
	buf.i = 0;
	while (expr[buf.i])
	{
		if (is_var_char_start(expr[buf.i]))
			buf.i = extract_and_expand_var(expr, buf.i, env, &buf);
		else
			buf.result[buf.k++] = expr[buf.i++];
	}
	buf.result[buf.k] = '\0';
	return (buf.result);
}
