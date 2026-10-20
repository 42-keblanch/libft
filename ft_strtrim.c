/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 19:54:36 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 19:54:38 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s, const char *set)
{
	int		start;
	int		len;
	char	*r;

	start = 0;
	while (s[start] && ft_strchr(set, s[start]))
		++start;
	len = ft_strlen(s + start);
	while (len > 0 && ft_strchr(set, s[start + len - 1]))
		--len;
	r = ft_substr(s, start, len);
	return (r);
}
