/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:14 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/16 12:22:50 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != 0 && s2[i] != 0)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
	result = ft_strncmp((const char*)argv[1], (const char*)argv[2], 
		(size_t)ft_atoi(argv[3]));
	printf("%d", result);
	return (0);
}*/