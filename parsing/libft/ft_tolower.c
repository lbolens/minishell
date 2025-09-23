/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:21:58 by lbolens           #+#    #+#             */
/*   Updated: 2025/04/15 13:37:34 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c += 32);
	return (c);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	int	result;

	if (argc != 2)
	{
		printf("Please put one variable");
		return (0);
	}
	result = ft_tolower(argv[1][0]);
	printf("%d", result);
	return (0);
}*/