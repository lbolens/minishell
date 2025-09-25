/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:57:45 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/25 11:28:20 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

t_token	*ft_lstnew(void *content)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = define_type(content);
	node->value = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

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
