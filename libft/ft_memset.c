/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:06:28 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 10:37:44 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*stri;
	unsigned char		c1;

	if (s == 0)
		return (0);
	c1 = (unsigned char)c;
	i = 0;
	stri = (unsigned char*)s;
	while (i < n)
	{
		stri[i] = c1;
		i++;
	}
	return (stri);
}
