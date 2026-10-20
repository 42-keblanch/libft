/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keblanch <keblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 16:54:41 by keblanch          #+#    #+#             */
/*   Updated: 2026/10/20 17:29:52 by keblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	ret;
	int	negative;

	i = 0;
	ret = 0;
	negative = 1;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative *= -1;
		++i;
	}
	while (ft_isdigit(str[i]))
	{
		ret *= 10;
		ret += str[i] - '0';
		++i;
	}
	return (ret * negative);
}
