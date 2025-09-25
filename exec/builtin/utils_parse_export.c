/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:47:37 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 11:29:26 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

int	parse_export(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*extract_var(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var_name = (char *)malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, str, i);
	var_name[i] = '\0';
	return (var_name);
}

char	*extract_value(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*value;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	value = (char *)malloc(sizeof(char) * ((len - i) + 1));
	if (!value)
		return (NULL);
	i++;
	while (str[i])
	{
		value[j] = str[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}
