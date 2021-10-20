/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:14:43 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/15 22:58:17 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		cpt;
	char	*flags;
	int		*width;

	i = 0;
	cpt = 0;
	va_start(ap, str);
	while (str[i] && cpt >= 0)
	{
		if (skip_chars(str, &i, &cpt) == 1)
		{
			flags = gestion_flags(str, &i);
			width = gestion_width(str, &i);
			width[0] = (width[0] == -1) ? va_arg(ap, int) : width[0];
			width[1] = (width[1] == -1) ? va_arg(ap, int) : width[1];
			cpt += gestion_arg(str[i], &ap, flags, width);
			free(flags);
			free(width);
			i++;
		}
	}
	va_end(ap);
	return (cpt);
}
