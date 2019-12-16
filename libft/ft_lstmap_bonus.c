/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:47:53 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/14 13:47:55 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*))
{
	t_list	*new;
	t_list	*node;
	t_list	*begin;

	node = 0;
	if (lst && f)
	{
		begin = ft_lstnew(f(lst->content));
		node = begin;
		lst = lst->next;
		while (lst)
		{
			new = ft_lstnew(f(lst->content));
			node->next = new;
			node = new;
			lst = lst->next;
		}
		return (begin);
	}
	else
		return (0);
}
