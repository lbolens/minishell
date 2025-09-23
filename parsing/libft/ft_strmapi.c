/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:38:05 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:16:04 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	size;
	char			*dest;

	if (!s || !f)
		return (NULL);
	size = 0;
	while (s[size] != 0)
		size++;
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*char	to_upper_on_even(unsigned int i, char c)
{
	if (i % 2 == 0 && c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

#include <stdio.h>
int	main(int argc, char** argv)
{
	char* result;

	if (argc != 2)
	{
		printf("please put one variable");
		return (0);
	}
	result = ft_strmapi(argv[1], &to_upper_on_even);
	printf("%s", result);
	return (0);
}*/