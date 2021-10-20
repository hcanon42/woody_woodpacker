/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:55:35 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/14 13:48:38 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1)
		{
			if (src[i] != 0)
				dst[i] = src[i];
			else
			{
				dst[i] = 0;
				return (ft_strlen(src));
			}
			i++;
		}
		dst[i] = 0;
	}
	return (ft_strlen(src));
}
