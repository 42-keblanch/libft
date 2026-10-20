/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:51:45 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:51:56 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	r;
	size_t	i;

	i = 0;
	r = ft_strlen(src);
	if (size <= 0)
		return (r);
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (r);
}
