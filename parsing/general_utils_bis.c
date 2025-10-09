/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:40:44 by lbolens           #+#    #+#             */
/*   Updated: 2025/10/09 14:41:01 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

size_t	ft_strlcpy_pars(char *dest, const char *src, size_t dstsize)
{
	size_t	l_src;

	l_src = ft_strlen_pars(src);
	if (dstsize > l_src + 1)
		ft_memcpy_pars(dest, src, l_src + 1);
	else if (dstsize != 0)
	{
		ft_memcpy_pars(dest, src, dstsize - 1);
		dest[dstsize - 1] = '\0';
	}
	return (l_src);
}

int	ft_strncmp_pars(const char *s1, const char *s2, size_t n)
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

int	count_size(long nb)
{
	int		count;
	long	num;

	num = nb;
	count = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num = num * -1;
		count++;
	}
	while (num > 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa_pars(int n)
{
	int		size;
	long	nbr;
	char	*dest;

	nbr = n;
	size = count_size(nbr);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	if (nbr == 0)
		dest[0] = '0';
	if (nbr < 0)
	{
		dest[0] = '-';
		nbr = nbr * -1;
	}
	dest[size] = '\0';
	while (nbr > 0)
	{
		dest[size - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		size--;
	}
	return (dest);
}
