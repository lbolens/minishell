/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:36:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 11:36:20 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

static void	free_array_on_error(char **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	*create_env_string(t_env_var *node)
{
	char	*str;
	int		len;

	len = ft_strlen_pars(node->name) + ft_strlen_pars(node->value) + 2;
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy_pars(str, node->name, len);
	ft_strlcat(str, "=", len);
	ft_strlcat(str, node->value, len);
	return (str);
}

static int	fill_env_array(char **array, t_env_var *list)
{
	t_env_var	*current;
	int			i;

	current = list;
	i = 0;
	while (current)
	{
		array[i] = create_env_string(current);
		if (!array[i])
		{
			free_array_on_error(array, i);
			return (0);
		}
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (1);
}

char	**env_list_to_array(t_env_var *list)
{
	char	**array;
	int		count;

	count = ft_lstsize_pars(list);
	array = malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (!fill_env_array(array, list))
		return (NULL);
	return (array);
}
