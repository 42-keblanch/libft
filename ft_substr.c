/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:59:29 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 20:05:36 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	rlen;
	size_t	slen;

	slen = ft_strlen(s);
	if (start >= slen)
	{
		r = ft_calloc(1, 1);
		if (!r)
			return (NULL);
		return (r);
	}
	slen = ft_strlen(s + start);
	if (len > slen)
		rlen = slen + 1;
	else
		rlen = len + 1;
	r = ft_calloc(rlen, sizeof(char));
	if (!r)
		return (NULL);
	ft_strlcpy(r, s + start, rlen);
	return (r);
}
