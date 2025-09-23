/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:44:57 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 15:42:06 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	i = 0;
	cc = (char)c;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	char* result = NULL;

	if (argc != 2)
	{
		printf("Please put 2 variables");
		return (0);
	}
	result = strchr(result, argv[1][0]);
	if (result == NULL)
		printf("Character not found");
	else
		printf("%s", result);
	return (0);
}*/