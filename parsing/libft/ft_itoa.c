/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:40:47 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 11:04:47 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int num)
{
	int		size;
	long	n;

	n = num;
	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n >= 10)
	{
		n = n / 10;
		size++;
	}
	size++;
	return (size);
}

char	*ft_putnbr(int n, char *s, int size, int *i)
{
	long	a;

	a = n;
	if (a < 0)
	{
		s[*i] = '-';
		(*i)++;
		a *= -1;
	}
	if (a >= 10)
		ft_putnbr(a / 10, s, size, i);
	s[*i] = (a % 10) + '0';
	(*i)++;
	return (s);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		size;
	int		i;

	size = ft_size(n);
	s = (char *)malloc((size + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	s = ft_putnbr(n, s, size, &i);
	s[size] = '\0';
	return (s);
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	char*	result;
	char* result2;

	if (argc != 2)
	{
		printf("Please put one variable");
		return (0);
	}
	result = ft_itoa(ft_atoi(argv[1]));
	printf("%s, %s", result, result2);
	return (0);
}*/