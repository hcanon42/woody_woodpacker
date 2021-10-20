/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:23:09 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/10 14:45:58 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		i;
	char		*str;

	i = -1;
	if (!(str = malloc(size * count)))
		return (0);
	while (++i < count)
		str[i] = 0;
	return ((void *)str);
}
