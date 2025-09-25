/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlongin <hlongin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:49:56 by hlongin           #+#    #+#             */
/*   Updated: 2025/09/25 11:53:53 by hlongin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parsing.h"

char	*find_command_path(char *cmd_name, char **envp)
{
	char	**paths;
	char	*result;

	if (!cmd_name || !cmd_name[0])
		return (NULL);
	if (has_slash(cmd_name))
		return (try_command_with_slash(cmd_name));
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	result = search_command_in_paths(cmd_name, paths);
	free_tab(paths);
	return (result);
}

char	**get_paths(char **envp)
{
	const char	*val;
	int			count;

	val = find_path_value(envp);
	if (!val)
		return (NULL);
	count = count_segments(val);
	if (count <= 0)
		return (NULL);
	return (fill_segments(val, count));
}

char	*join3(const char *a, const char *b, const char *c)
{
	int		total_len;
	int		i;
	char	*s;

	total_len = calculate_total_length(a, b, c);
	s = (char *)malloc(total_len + 1);
	if (!s)
		return (NULL);
	i = 0;
	while (a && *a)
		s[i++] = *a++;
	while (b && *b)
		s[i++] = *b++;
	while (c && *c)
		s[i++] = *c++;
	s[i] = '\0';
	return (s);
}

char	*build_candidate(const char *dir, const char *cmd)
{
	if (dir && dir[0] == '.' && dir[1] == '\0')
		return (join3("./", "", cmd));
	return (join3(dir, "/", cmd));
}
