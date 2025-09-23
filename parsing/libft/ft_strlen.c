/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:12 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:10:54 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	size_t	result;

	if (argc != 2)
	{
		printf("Please put one variable");
		return (0);
	}
	result = ft_strlen((const char*)argv[1]);
	printf("%ld", result);
	return (0);
}*/