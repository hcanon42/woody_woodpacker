/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:02:40 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/09 17:52:23 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dest;
	const char	*source;

	i = -1;
	source = (char *)src;
	dest = (char *)dst;
	if (dest < source)
		while (++i < len)
			dest[i] = source[i];
	else
	{
		while (len-- > 0)
			dest[len] = source[len];
	}
	return (dst);
}
