/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:09 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:08:38 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	l_src;

	l_src = ft_strlen(src);
	if (dstsize > l_src + 1)
		ft_memcpy(dest, src, l_src + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dest, src, dstsize - 1);
		dest[dstsize - 1] = '\0';
	}
	return (l_src);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	size_t result;
	char dest[100];

	if (argc != 3)
	{
		printf("Please put 2 variables");
		return (0);
	}
	result = ft_strlcpy(dest, (const char*)argv[1], (size_t)ft_atoi(argv[2]));
	printf("%ld", result);
	return (0);
}*/