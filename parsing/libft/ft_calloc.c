/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:44:25 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 10:42:42 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;

	if (count > 0 && size > SIZE_MAX / count)
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	unsigned char* result;
	int	i;

	if (argc != 3)
	{
		printf("Please put 2 numbers");
		return (0);
	}
	result = ft_calloc(ft_atoi(argv[1]), ft_atoi(argv[2]));
	i = 0;
	while (i < (ft_atoi(argv[1]) * ft_atoi(argv[2])))
	{
		printf("%d", result[i]);
		i++;
	}
	return (0);
}*/