/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:51:02 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:53:51 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	size_t	len1;
	size_t	len2;
	char	*r;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1 + len2;
	r = ft_calloc(len + 1, sizeof(char));
	if (!r)
		return (NULL);
	ft_memcpy(r, s1, len1);
	ft_memcpy(r + len1, s2, len2);
	return (r);
}
