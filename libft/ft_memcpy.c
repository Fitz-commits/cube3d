/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:25:01 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 11:29:54 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*dstr;
	const unsigned char		*sstr;
	size_t					i;

	if (dest == 0)
		return (0);
	dstr = (unsigned char*)dest;
	sstr = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		dstr[i] = sstr[i];
		i++;
	}
	return (dest);
}
