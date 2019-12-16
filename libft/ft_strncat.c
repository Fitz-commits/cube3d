/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:47:58 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/09 13:48:00 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	unsigned int	i;
	int				i2;

	i = 0;
	while (dest[i])
		i++;
	i2 = i;
	i = 0;
	while (src[i] && i < nb)
	{
		dest[i2] = src[i];
		i++;
		i2++;
	}
	dest[i2] = '\0';
	return (dest);
}
