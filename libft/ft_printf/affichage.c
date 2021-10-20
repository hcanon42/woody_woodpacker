/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:32:22 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/15 17:47:58 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_initialize(int *i, int *j, int *len, char *str)
{
	*j = 0;
	*i = -1;
	*len = ft_strlen(str);
	return (*len);
}

int			print(char *str, char *flags, int *width)
{
	int		i;
	int		j;
	char	*final_str;
	char	blank;
	int		len;

	blank = (in_str(flags, '0') && in_str(flags, '-') == 0) ? '0' : ' ';
	width[0] = (ft_initialize(&i, &j, &len, str) > width[0]) ? len : width[0];
	if (!(final_str = (char *)malloc(sizeof(char) * (width[0] + 1))))
		return (-1);
	if (in_str(flags, '-') == 1)
		while (++i < width[0])
			final_str[i] = (str[j]) ? str[j++] : blank;
	else
		while (++i < width[0])
			final_str[i] = (i < width[0] - len) ? blank : str[j++];
	if (i > width[1] && width[1] > 0)
		final_str[width[1]] = 0;
	else
		final_str[i] = 0;
	i = -1;
	while (final_str[++i])
		ft_putchar(final_str[i]);
	free(final_str);
	return (i);
}

static char	*recur_hexa(char *str, long n, int type)
{
	char	*hexa;
	char	reste[2];

	hexa = (type == 2) ? "0123456789ABCDEF" : "0123456789abcdef";
	reste[1] = '\0';
	if (n > 9)
		str = recur_hexa(str, n / 16, type);
	reste[0] = hexa[(unsigned char)(n % 16)];
	str = ft_strcat(str, reste);
	return (str);
}

char		*hexa(long n, int type)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * 14)))
		return (0);
	str[0] = 0;
	if (type == 3)
	{
		str[0] = '0';
		str[1] = 'x';
		str[2] = 0;
	}
	str = recur_hexa(str, n, type);
	return (str);
}
