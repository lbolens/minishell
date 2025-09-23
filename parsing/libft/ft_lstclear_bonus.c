/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:03:09 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 15:41:12 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*temp;

	while (*lst != 0)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	free(NULL);
	*lst = NULL;
}

/*void del(void *test)
{
	(void)test;
}

int	main(void)
{
	t_list *a = malloc((sizeof(t_list)));
	t_list *b = malloc((sizeof(t_list)));

	a->next = b;
	b->next = NULL;
	ft_lstclear(&a, &del);
}*/