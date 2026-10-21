/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:18:08 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/21 11:26:10 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	size_t	size;

	if (!lst)
		return (0);
	current = lst;
	size = 1;
	while (current->next)
	{
		current = current->next;
		++size;
	}
	return (size);
}
