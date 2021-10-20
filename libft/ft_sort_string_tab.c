/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 22:02:07 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/08 22:09:10 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

static int	tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

void		ft_sort_string_tab(char **tab)
{
	char	**a;
	char	**b;
	int		stack_de_swap;
	int		n;

	n = 0;
	if (tablen(tab) > 1)
	{
		stack_de_swap = tablen(tab);
		while (stack_de_swap > 0)
		{
			stack_de_swap--;
			a = &tab[n];
			b = &tab[n + 1];
			if (ft_strcmp(*a, *b) > 0)
			{
				swap(a, b);
				stack_de_swap = tablen(tab);
			}
			n++;
			if (n == tablen(tab) - 1)
				n = 0;
		}
	}
}
