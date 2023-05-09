/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:53:39 by yaysu             #+#    #+#             */
/*   Updated: 2022/12/11 22:32:26 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	unsigned int	i;
	char			*source;
	char			*dizi;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	i = 0;
	source = (char *)s;
	dizi = (char *)malloc(len + 1 * sizeof(char));
	if (!dizi)
		return (NULL);
	while (i < len)
	{
		dizi[i] = source[start + i];
		i++;
	}
	dizi[i] = '\0';
	return (dizi);
}
