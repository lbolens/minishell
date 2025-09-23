/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:19 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:26:35 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	int		i;
	char	*res;
	char	cc;

	i = 0;
	cc = (char)c;
	res = NULL;
	while (src[i])
	{
		if (src[i] == cc)
			res = ((char *)&src[i]);
		i++;
	}
	if (cc == src[i])
		res = ((char *)&src[i]);
	return (res);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	char* result;

	if (argc != 3)
	{
		printf("Please put 2 variables");
		return (0);	
	}
	result = ft_strrchr((const char*)argv[1], argv[2][0]);
	printf("%s", result);
	return (0);
}*/