/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 20:10:09 by htumanya          #+#    #+#             */
/*   Updated: 2021/01/30 18:58:53 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *allocated;

	if (!(allocated = malloc(count * size)))
		return (NULL);
	ft_memset(allocated, '\0', (count * size));
	return (allocated);
}
