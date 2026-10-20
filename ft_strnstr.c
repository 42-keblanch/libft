/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:52:53 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:53:18 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	needle_size;
	size_t	haystack_size;
	int		r;

	i = 0;
	needle_size = ft_strlen(needle);
	haystack_size = ft_strlen(haystack);
	if (needle_size == 0)
		return ((char *)haystack);
	if (haystack_size == 0 || n == 0 || n < needle_size)
		return (NULL);
	while (i + needle_size <= haystack_size && i + needle_size <= n)
	{
		if (haystack[i] == *needle)
		{
			r = ft_strncmp(haystack + i, needle, needle_size);
			if (r == 0)
				return ((char *)(haystack + i));
		}
		++i;
	}
	return (NULL);
}
