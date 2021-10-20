/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:31:00 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/15 19:37:40 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;
	size_t	j;

	if (!s)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (0);
	if ((size_t)start > ft_strlen(s))
	{
		str[0] = 0;
		return (str);
	}
	i = start;
	j = 0;
	while (s[i] && j < len)
		str[j++] = s[i++];
	str[j] = 0;
	return (str);
}
