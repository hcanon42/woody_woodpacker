/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:58:52 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/15 17:44:56 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		skip_chars(const char *str, int *i, int *cpt)
{
	while (str[*i])
	{
		if (str[*i] == '%')
			return (1);
		write(1, &str[*i], 1);
		(*i)++;
		(*cpt)++;
	}
	return (0);
}

char	*gestion_flags(const char *str, int *i)
{
	int		j;
	int		n;
	char	*flags;

	j = 0;
	if (!(flags = (char *)malloc(sizeof(char) * 6)))
		return (NULL);
	(*i)++;
	while ((str[*i] == '0' || str[*i] == '+' || str[*i] == '-' || str[*i] == ' '
					|| str[*i] == '#') && j < 5)
	{
		n = 0;
		flags[j++] = str[(*i)++];
		while (n + 1 < j)
			if (flags[n++] == str[(*i) - 1])
				flags[0] = 'Q';
	}
	flags[j] = 0;
	return (flags);
}

int		*gestion_width(const char *str, int *i)
{
	int		*width;

	if (!(width = (int *)malloc(sizeof(int) * 2)))
		return (NULL);
	width[0] = 0;
	width[1] = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
		width[0] = width[0] * 10 + str[(*i)++] - 48;
	if (str[*i] == '*' && width[0] == 0)
	{
		width[0] = -1;
		(*i)++;
	}
	if (str[*i] == '.')
		(*i)++;
	if (str[*i] == '*')
	{
		(*i)++;
		width[1] = -1;
		return (width);
	}
	while (str[*i] >= '0' && str[*i] <= '9' && width[1] != -1)
		width[1] = width[1] * 10 + str[(*i)++] - 48;
	return (width);
}

int		gestion_arg(char c, va_list *ap, char *flags, int *width)
{
	char	str[2];

	if (c == 'c')
	{
		str[0] = (unsigned char)va_arg(*ap, int);
		str[1] = 0;
		return (print(str, flags, width));
	}
	else if (c == 's')
		return (print(va_arg(*ap, char *), flags, width));
	else if (c == 'd' || c == 'i')
		return (print(ft_ltoa((long)va_arg(*ap, int)), flags, width));
	else if (c == 'u')
		return (print(ft_ltoa((long)va_arg(*ap, unsigned int)), flags, width));
	else if (c == 'x')
		return (print(hexa((long)va_arg(*ap, unsigned int), 1), flags, width));
	else if (c == 'X')
		return (print(hexa((long)va_arg(*ap, unsigned int), 2), flags, width));
	else if (c == 'p')
		return (print(hexa((long)va_arg(*ap, void *), 3), flags, width));
	else if (c == '%')
		return (print("%", flags, width));
	else
		return (-1);
}
