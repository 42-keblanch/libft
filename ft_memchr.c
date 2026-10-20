/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:38:36 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:39:58 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sb;
	unsigned char	cb;

	i = 0;
	sb = (unsigned char *)s;
	cb = (unsigned char)c;
	while (i < n)
	{
		if (sb[i] == cb)
			return (sb + i);
		++i;
	}
	return (NULL);
}
