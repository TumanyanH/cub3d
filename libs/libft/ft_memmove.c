/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:54:42 by htumanya          #+#    #+#             */
/*   Updated: 2021/01/30 18:58:43 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	buff[len];

	if (!dst && !src)
		return (NULL);
	ft_memcpy(buff, src, len);
	ft_memcpy(dst, buff, len);
	return (dst);
}
