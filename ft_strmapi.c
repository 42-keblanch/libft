/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:52:05 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:53:33 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*r;

	len = ft_strlen(s);
	r = (char *)ft_calloc(len + 1, sizeof(char));
	if (!r)
		return (NULL);
	i = 0;
	while (s[i])
	{
		r[i] = f(i, s[i]);
		++i;
	}
	return (r);
}
