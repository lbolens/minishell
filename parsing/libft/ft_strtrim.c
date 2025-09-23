/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:22 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/16 12:28:59 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_doing_it(const char *str, size_t start, size_t end)
{
	size_t	i;
	char	*trimmed;

	i = 0;
	if (end <= 0)
		return (ft_strdup(""));
	trimmed = ft_calloc(1 + end, sizeof(char));
	if (!trimmed)
		return (NULL);
	while (i < end)
	{
		trimmed[i] = str[start + i];
		i++;
	}
	return (trimmed);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1);
	if (j == 0)
		return (ft_strdup(""));
	j = j - 1;
	while (ft_check(s1[i], set))
		i++;
	if (i > j)
		return (ft_strdup(""));
	while (ft_check(s1[j], set))
		j--;
	return (ft_doing_it(s1, i, j - i + 1));
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	char* result;

	if (argc != 3)
	{
		printf("Please put 2 variables");
		return (0);
	}
	result = ft_strtrim((const char*)argv[1], (const char*)argv[2]);
	printf("%s", result);
	return (0);
}*/