/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:44:01 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:50:19 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

/*#include <stdio.h>
void	print_list(t_list* lst)
{
	while (lst)
	{
		printf("%s -> ", (char*)lst->content);
		lst = lst->next;
	}
	printf("NULL");
}

int	main(void)
{
	t_list* head = NULL;

	t_list *n1 = ft_lstnew("Hello");
	t_list *n2 = ft_lstnew("World");
	t_list *n3 = ft_lstnew("42");

	ft_lstadd_front(&head, n1);
	ft_lstadd_front(&head, n2);
	ft_lstadd_front(&head, n3);

	print_list(head);

	return (0);
}*/