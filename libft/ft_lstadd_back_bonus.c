/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 21:06:39 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/15 19:40:56 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*elem;

	if (!alst)
		return ;
	elem = *alst;
	if (!elem)
		*alst = new;
	else
	{
		while (elem->next != 0)
			elem = elem->next;
		elem->next = new;
	}
}
