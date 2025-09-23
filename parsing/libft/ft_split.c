/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:23:26 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/16 14:49:04 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char **dest, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

int	ft_nbr_words(const char *s, char c)
{
	int		nbr;
	int		i;

	i = 0;
	nbr = 0;
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
		{
			nbr++;
			while (s[i] != 0 && s[i] != c)
				i++;
		}
	}
	return (nbr);
}

char	*ft_fill_dest(const char *start, const char *end)
{
	int		size;
	int		i;
	char	*dest;

	size = end - start;
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dest[i] = start[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_doing_split(const char *s, char c, char **dest)
{
	int			i;
	int			j;
	const char	*start;

	i = 0;
	j = 0;
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0)
		{
			start = &s[i];
			while (s[i] != 0 && s[i] != c)
				i++;
			dest[j] = ft_fill_dest(start, &s[i]);
			if (dest[j] == NULL)
				return (ft_free_tab(dest, j), NULL);
			j++;
		}
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(const char *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	dest = (char **)malloc((ft_nbr_words(s, c) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	return (ft_doing_split(s, c, dest));
}

/*#include <stdio.h>
int	main(int argc, char** argv)
{
	char** result;
	int	i;

	if (argc != 3)
	{
		printf("Please put 2 variables");
		return (0);
	}
	result = ft_split(argv[1], (char)argv[2][0]);
	i = 0;
	while (result[i] != NULL)
	{
		printf("%s\n", result[i]);
		i++;
	}
	return (0);
}*/