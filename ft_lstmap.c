/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:40:23 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/21 15:33:01 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_curr;
	t_list	*lst_curr;

	if (!lst)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	new_curr = new;
	lst_curr = lst;
	while (lst_curr->next)
	{
		lst_curr = lst_curr->next;
		new_curr->next = ft_lstnew(f(lst_curr->content));
		if (!new_curr->next)
		{
			ft_lstclear(&new, del);
			return (new);
		}
		new_curr = new_curr->next;
	}
	return (new);
}
