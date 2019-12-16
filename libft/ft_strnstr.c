/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:37:15 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/08 09:37:21 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	unsigned int	i;
	unsigned int	a;
	int				j;

	i = 0;
	j = 0;
	a = 0;
	if (ft_strlen(to_find) == 0)
		return ((char*)str);
	while (str[i] && i < n)
	{
		a = i;
		j = 0;
		if (str[i] == to_find[0])
			while (str[a] == to_find[j] && a < n)
			{
				if (j == ft_strlen(to_find) - 1)
					return ((char*)&str[i]);
				a++;
				j++;
			}
		i++;
	}
	return (0);
}
