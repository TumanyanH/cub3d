/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:33:58 by htumanya          #+#    #+#             */
/*   Updated: 2021/01/28 19:35:38 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1len;
	char	*str;

	s1len = ft_strlen(s1);
	if (!(str = malloc(sizeof(char) * (s1len + 1))))
		return (NULL);
	while (*s1 != '\0')
	{
		*str = *s1;
		++str;
		++s1;
	}
	*str = '\0';
	return (str - s1len);
}
