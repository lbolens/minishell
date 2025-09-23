/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:44:40 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/16 12:47:37 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	unsigned char			b;
	const unsigned char		*str;

	b = (unsigned char)c;
	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == b)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	void*	result;

	if (argc != 4)
	{
		printf("Please put 3 variables");
		return (0);
	}
	result = memchr(NULL, argv[2][0], (size_t)ft_atoi(argv[3]));
	if (result != NULL)
		printf ("%c", *(unsigned char*)result);
	else
		printf("Character not found");
	return (0);
}*/