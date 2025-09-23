/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:17 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:41:20 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len && haystack[i + j])
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	char* result;

	if (argc != 4)
	{
		printf("Please put 3 variables");
		return (0);
	}
	result = ft_strnstr((const char*)argv[1], (const char*)argv[2], 
		(size_t)ft_atoi(argv[3]));
	printf("%s", result);
	return (0);
}*/