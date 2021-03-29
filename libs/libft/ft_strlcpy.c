/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:31:35 by htumanya          #+#    #+#             */
/*   Updated: 2021/01/25 19:34:45 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned char	*source;
	size_t			i;

	source = (unsigned char *)src;
	i = 0;
	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	while (src[i] != '\0')
	{
		if (i < dstsize - 1)
		{
			*dst = *source;
			++dst;
			++source;
		}
		++i;
	}
	*dst = '\0';
	return (i);
}
