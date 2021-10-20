/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:15:25 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/17 16:02:52 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*recur(char *str, int n)
{
	char	reste[2];

	reste[1] = '\0';
	if (n > 9)
		str = recur(str, n / 10);
	reste[0] = (unsigned char)((n % 10) + 48);
	str = ft_strcat(str, reste);
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * 12)))
		return (0);
	str[0] = 0;
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		str[2] = 0;
		n = 147483648;
	}
	else if (n < 0)
	{
		str[0] = '-';
		str[1] = '\0';
		n = -n;
	}
	str = recur(str, n);
	return (str);
}
