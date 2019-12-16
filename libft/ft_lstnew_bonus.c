/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:23:42 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/10 13:23:45 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list *newl;

	if (content)
	{
		if (!(newl = (t_list*)malloc(sizeof(t_list))))
			return (0);
		newl->content = (void*)(content);
		newl->next = 0;
		return (newl);
	}
	return (NULL);
}
