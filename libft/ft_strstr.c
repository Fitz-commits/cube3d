/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:36:47 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/08 09:36:50 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int a;
	int j;

	i = 0;
	j = 0;
	a = 0;
	while (str[i])
	{
		a = i;
		j = 0;
		if (str[i] == to_find[0])
			while (str[a] == to_find[j])
			{
				if (j == ft_strlen(to_find) - 1)
					return (&str[i]);
				a++;
				j++;
			}
		i++;
	}
	if (ft_strlen(to_find) == 0)
		return (str);
	else
		return (0);
}
