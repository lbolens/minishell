/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:44:45 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/16 12:39:44 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*dest2;
	const unsigned char		*src2;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dest2 = (unsigned char *)dest;
	src2 = (const unsigned char *)src;
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	void* result;
	char dest[100];

	if (argc != 3)
	{
		printf("Please put 2 variables");
		return (0);
	}
	result = ft_memcpy(dest, argv[1], (size_t)ft_atoi(argv[2]));
	printf("%s", dest);
	return (0);
}*/