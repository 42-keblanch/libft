/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:52:39 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:52:48 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1b;
	unsigned char	*s2b;

	i = 0;
	s1b = (unsigned char *)s1;
	s2b = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n && s1b[i] == s2b[i] && s1b[i] != 0)
		++i;
	if (i == n)
		--i;
	return (s1b[i] - s2b[i]);
}
