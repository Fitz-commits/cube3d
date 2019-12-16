/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:15:52 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/09 11:15:56 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*dstr;
	unsigned char		*sstr;
	size_t				i;

	dstr = (unsigned char*)dest;
	sstr = (unsigned char*)src;
	if (dest == 0 && src == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		dstr[i] = sstr[i];
		if (dstr[i] == (unsigned char)c)
		{
			return (&dest[i + 1]);
		}
		i++;
	}
	return (0);
}
