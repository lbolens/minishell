/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:28 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:39:14 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c -= 32);
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
	result = ft_toupper(argv[1][0]);
	printf("%d", result);
	return (0);
}*/