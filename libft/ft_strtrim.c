/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:44:27 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/15 19:37:10 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inset(char c, char const *set)
{
	int		i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

static int	cpt_fin(char const *str, char const *set)
{
	int		i;
	int		cpt;

	cpt = 0;
	i = ft_strlen(str) - 1;
	while (inset(str[i], set) == 1 && i > 0)
	{
		cpt++;
		i--;
	}
	return (cpt);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		cpt_start;
	int		i;

	i = 0;
	cpt_start = 0;
	if (!s1 || !set)
		return (NULL);
	while (inset(s1[cpt_start], set) == 1 && s1[cpt_start])
		cpt_start++;
	if (!s1[cpt_start])
		return (ft_strdup(""));
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1 - cpt_start -
						cpt_fin(s1, set)))))
		return (NULL);
	while (cpt_start < (int)ft_strlen(s1) - cpt_fin(s1, set))
		str[i++] = s1[cpt_start++];
	str[i] = 0;
	return (str);
}
