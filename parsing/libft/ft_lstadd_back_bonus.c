/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:33:09 by lucasbolens       #+#    #+#             */
/*   Updated: 2025/04/15 13:48:40 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
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

	ft_lstadd_back(&head, n1);
	ft_lstadd_back(&head, n2);
	ft_lstadd_back(&head, n3);

	print_list(head);

	return (0);
}*/