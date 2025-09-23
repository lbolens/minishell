/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:07 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:04:05 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	l_dest;
	size_t	l_src;

	l_dest = ft_strlen(dest);
	l_src = ft_strlen(src);
	if (l_dest >= dstsize)
		l_dest = dstsize;
	if (l_dest == dstsize)
		return (dstsize + l_src);
	if (l_src < dstsize - l_dest)
		ft_memcpy(dest + l_dest, src, l_src + 1);
	else
	{
		ft_memcpy(dest + l_dest, src, dstsize - l_dest - 1);
		dest[dstsize - 1] = '\0';
	}
	return (l_dest + l_src);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	size_t result;

	if (argc != 4)
	{
		printf("Please put 3 variables");
		return (0);
	}
	result = ft_strlcat(argv[1], (const char*)argv[2], (size_t)ft_atoi(argv[3]));
	printf("%ld", result);
	return (0);
}*/