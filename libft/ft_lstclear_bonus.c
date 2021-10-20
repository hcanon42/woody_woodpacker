/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 21:23:17 by hcanon            #+#    #+#             */
/*   Updated: 2019/10/15 19:42:00 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;

	if (!lst || !del)
		return ;
	elem = *lst;
	while (elem != 0)
	{
		(*del)(elem->content);
		free(elem);
		elem = elem->next;
	}
	*lst = 0;
}
