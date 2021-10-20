/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 22:06:24 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/09 17:59:18 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(char *s1, char *s2)
{
	int		c;

	c = 0;
	while ((s1[c] != '\0') && (s2[c] != '\0'))
	{
		if (s1[c] != s2[c])
			return ((unsigned char)s1[c] - (unsigned char)s2[c]);
		c++;
	}
	if (s1[c] != s2[c])
		return ((unsigned char)s1[c] - (unsigned char)s2[c]);
	return (0);
}
