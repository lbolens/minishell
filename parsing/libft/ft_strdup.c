/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:01 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/16 12:47:56 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	size;
	char	*dest;

	i = 0;
	size = 0;
	while (s1[size] != 0)
		size++;
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1[i] != 0)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	char* result;

	if (argc != 2)
	{
		printf("Please put one variable");
		return (0);
	}
	result = ft_strdup((const char*)argv[1]);
	printf("%s", result);
	return (0);
}*/