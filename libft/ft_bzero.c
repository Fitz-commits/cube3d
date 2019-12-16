/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:08:14 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 10:18:21 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*sc;

	if (s == 0)
		return ;
	i = 0;
	sc = (unsigned char*)s;
	while (i < n)
	{
		sc[i] = 0;
		i++;
	}
}
