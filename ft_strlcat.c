/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:51:30 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:51:40 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;

	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	i = dst_size;
	if (size <= 0)
		return (src_size);
	while (i < size - 1 && src[i - dst_size] != '\0')
	{
		dst[i] = src[i - dst_size];
		++i;
	}
	dst[i] = '\0';
	if (size < dst_size)
		return (size + src_size);
	return (dst_size + src_size);
}
