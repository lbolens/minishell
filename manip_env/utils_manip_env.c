/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_manip_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:28:48 by lbolens           #+#    #+#             */
/*   Updated: 2025/09/30 14:30:15 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parsing.h"

void	ft_lstdelone_pars(t_env_var *lst)
{
	if (!lst)
		return ;
	free(lst->name);
	free(lst->value);
	free(lst);
}

void	ft_lstclear_pars(t_env_var **lst)
{
	t_env_var	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_pars(*lst);
		*lst = tmp;
	}
}

int	ft_lstsize_pars(t_env_var *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// Ajouter variable a la liste
void	add_env_var(t_env_var **list, char *env_string)
{
	t_env_var	*temp;
	t_env_var	*new;

	new = create_new_env_var(env_string);
	if (!list || !new)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
