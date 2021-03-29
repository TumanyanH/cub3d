/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:02:21 by htumanya          #+#    #+#             */
/*   Updated: 2021/01/30 18:57:51 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	s += start;
	while (i < len && *s != '\0')
	{
		*str = *s;
		++str;
		++s;
		i++;
	}
	*str = '\0';
	return (str - len);
}
