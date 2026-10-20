/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:43:08 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:43:36 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	t;

	i = 0;
	while (i < n)
	{
		if (dest < src)
			t = i;
		else
			t = n - i - 1;
		((unsigned char *)dest)[t] = ((unsigned char *)src)[t];
		++i;
	}
	return (dest);
}
