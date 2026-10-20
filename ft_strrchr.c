/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:54:06 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:54:25 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*sb;
	unsigned char	cb;

	i = ft_strlen(s);
	sb = (unsigned char *)s;
	cb = (unsigned char)c;
	while (i > 0)
	{
		if (sb[i] == cb)
			return ((char *)s + i);
		--i;
	}
	if (sb[0] == cb)
		return ((char *)s);
	return (NULL);
}
