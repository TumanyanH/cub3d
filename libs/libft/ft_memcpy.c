/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:59:04 by htumanya          #+#    #+#             */
/*   Updated: 2021/01/30 18:58:32 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*source;
	unsigned char		*temp;

	source = (const unsigned char *)src;
	temp = (unsigned char *)dst;
	if (!dst && !src)
		return (NULL);
	while (n)
	{
		*temp = *source;
		++source;
		++temp;
		--n;
	}
	return (dst);
}
