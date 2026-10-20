/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 17:24:37 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 17:28:43 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*s;
	size_t			i;

	s = 0;
	i = 0;
	if (nmemb != 0 && (UINT_MAX / nmemb < size))
		return (s);
	s = malloc(nmemb * size);
	if (!s)
		return (s);
	while (i < nmemb * size)
	{
		s[i] = 0;
		++i;
	}
	return ((void *)s);
}
