/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:58:24 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/15 16:58:58 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*recur_long(char *str, long n)
{
	char	reste[2];

	reste[1] = '\0';
	if (n > 9)
		str = recur_long(str, n / 10);
	reste[0] = (unsigned char)((n % 10) + 48);
	str = ft_strcat(str, reste);
	return (str);
}

char		*ft_ltoa(long n)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * 12)))
		return (0);
	str[0] = 0;
	if (n < 0)
	{
		str[0] = '-';
		str[1] = '\0';
		n = -n;
	}
	str = recur_long(str, n);
	return (str);
}
