/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htumanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:07:33 by htumanya          #+#    #+#             */
/*   Updated: 2021/01/30 18:57:24 by htumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
		{
			return (1);
		}
		++set;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		a;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && check_set(s1[i], set))
		++i;
	len = ft_strlen(s1 + i);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	a = j--;
	while (check_set(str[j], set) && len)
	{
		str[j--] = '\0';
		--len;
	}
	str[a] = '\0';
	return (str);
}
