/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:50:08 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:50:21 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*sb;
	unsigned char	cb;

	i = 0;
	sb = (unsigned char *)s;
	cb = (unsigned char)c;
	while (sb[i] != '\0')
	{
		if (sb[i] == cb)
			return ((char *)s + i);
		++i;
	}
	if (sb[i] == cb)
		return ((char *)s + i);
	return (0);
}
