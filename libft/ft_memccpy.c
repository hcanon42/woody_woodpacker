/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:57:49 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/08 17:41:11 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	char		*dest;
	char		*source;

	i = -1;
	dest = (char *)dst;
	source = (char *)src;
	while (++i < n)
	{
		dest[i] = source[i];
		if (dest[i] == (unsigned char)c)
			return (&dest[++i]);
	}
	return (0);
}
