/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 18:46:38 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:40:33 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*t;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(s) + 1;
	t = (char *)ft_calloc(size, sizeof(char));
	if (!t)
		return (NULL);
	while (i < size)
	{
		t[i] = s[i];
		++i;
	}
	return (t);
}
