/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:44:42 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:40:52 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*str1;
	const unsigned char		*str2;

	if (n == 0)
		return (0);
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	int	result;

	if (argc != 4)
	{
		printf("Please put 3 variables");
		return (0);
	}
	result = ft_memcmp((const void*)argv[1], (const void*)argv[2], 
		(size_t)ft_atoi(argv[3]));
	printf("%d", result);
	return (0);
}*/