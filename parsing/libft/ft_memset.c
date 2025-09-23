/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:44:55 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/16 12:47:07 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)s;
	while (i < n)
	{
		dest[i] = (unsigned char)c;
		i++;
	}
	return (s);
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
	result = ft_memset(dest, argv[1][0], (size_t)ft_atoi(argv[2]));
	printf("%s", dest);
	return (0);
}*/