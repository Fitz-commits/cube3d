/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:13:09 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 11:29:36 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*sstr;

	sstr = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (sstr[i] == (unsigned char)c)
			return (&sstr[i]);
		i++;
	}
	return (0);
}
