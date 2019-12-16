/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:33:19 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 11:59:25 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*str1a;
	const unsigned char		*str2a;

	str1a = (unsigned char*)s1;
	str2a = (unsigned char*)s2;
	i = 0;
	while (i < n)
	{
		if (str1a[i] != str2a[i])
			return (str1a[i] - str2a[i]);
		i++;
	}
	return (0);
}
