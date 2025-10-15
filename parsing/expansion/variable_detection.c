/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_detection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:43:46 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/15 11:11:49 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

bool	is_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void	replace_in_command(t_cmd *commands, char *str, int i)
{
	free(commands->args[i]);
	commands->args[i] = ft_strdup_pars(str);
}

char	*extract_variable(char *str)
{
	char	*variable;
	char	temp[4096];
	int		i;
	int		j;

	variable = NULL;
	i = 0;
	j = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (str[i] == '$')
		i++;
	while (str[i] && str[i] != '/' && str[i] != ' ' && str[i] != '\0')
	{
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	variable = ft_strdup_pars(temp);
	return (variable);
}

char	*extract_chain(char *str, int start, int end)
{
	int		size;
	char	*result;
	int		i;

	size = end - start;
	result = malloc((size + 1) * sizeof(char));
	i = 0;
	if (!result)
		return (NULL);
	while (start < end)
	{
		result[i] = str[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}
