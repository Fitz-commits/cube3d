/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 08:50:43 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/08 08:41:03 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long				power(long nbr, int base)
{
	long j;

	j = nbr;
	if (base == 1)
		return (nbr);
	if (base == 0)
		return (1);
	while (base > 1)
	{
		nbr *= j;
		base--;
	}
	return (nbr);
}

static int				checksign(long nbr)
{
	if (nbr >= 0)
		return (0);
	else
		return (1);
}

char					*ft_itoa(long nbr)
{
	int				i;
	int				size;
	unsigned long	unbr;
	char			*cnbr;
	int				placeneg;

	i = 0;
	placeneg = checksign(nbr);
	size = get_size(nbr, 10);
	if (!(cnbr = malloc(sizeof(char) * (size + 1 + placeneg))))
		return (0);
	if (placeneg == 1)
	{
		cnbr[0] = '-';
		i = 1;
	}
	unbr = nbr * (1 - (2 * placeneg));
	while (size != 0)
	{
		cnbr[i++] = unbr / power(10, size - 1) + 48;
		unbr = unbr % power(10, size-- - 1);
	}
	cnbr[i] = 0;
	return (cnbr);
}
