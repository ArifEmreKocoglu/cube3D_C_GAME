/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:50:02 by yaysu             #+#    #+#             */
/*   Updated: 2022/12/11 22:24:25 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	a(char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			i++;
		s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**dizi;
	size_t	i;
	size_t	j;
	size_t	z;

	if (!s)
		return (NULL);
	dizi = (char **)malloc((a((char *)s, c) + 1) * sizeof(char *));
	if (!dizi)
		return (NULL);
	i = 0;
	j = 0;
	z = 0;
	while (i <= ft_strlen(s) && a((char *)s, c) != 0 && z < a((char *)s, c))
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] && s[i + j] != c)
			j++;
		dizi[z++] = ft_substr(s, i, j);
		i += j;
	}
	dizi[z] = 0;
	return (dizi);
}
