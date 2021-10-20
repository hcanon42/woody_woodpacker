/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 19:01:35 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/10 17:26:57 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strcpy(char *dest, const char *src)
{
	int		c;

	c = 0;
	while (src[c] != '\0')
	{
		dest[c] = src[c];
		c++;
	}
	dest[c] = '\0';
	return (dest);
}

char			*ft_strdup(const char *src)
{
	char	*str;
	int		n;

	n = 0;
	while (src[n])
		n++;
	if (!(str = (char*)malloc(sizeof(char) * n + 1)))
		return (str);
	str = ft_strcpy(str, src);
	return (str);
}
