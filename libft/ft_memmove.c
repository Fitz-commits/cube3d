/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:42:11 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 11:12:52 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char			*dstr;
	const unsigned char		*sstr;
	size_t					i;

	i = -1;
	if (!dest && !src)
		return (0);
	dstr = (unsigned char*)dest;
	sstr = (unsigned char*)src;
	if (dstr < sstr)
		while (++i < len)
			dstr[i] = sstr[i];
	else
		while (len-- > 0)
			dstr[len] = sstr[len];
	return (dstr);
}
