/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 23:48:03 by htumanya          #+#    #+#             */
/*   Updated: 2021/01/24 23:51:10 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *start;

	start = (const char *)s;
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s)
		++s;
	while (s >= start)
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s--;
	}
	return (NULL);
}
