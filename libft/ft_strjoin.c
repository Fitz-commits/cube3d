/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:14:29 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/09 16:24:45 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char			*concat;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	if (!(concat = (char*)malloc(sizeof(char) * (ft_strlen(s1)
		+ ft_strlen(s2) + 1))))
		return (0);
	while (s1[i])
	{
		concat[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		concat[i + j] = s2[j];
		j++;
	}
	concat[i + j] = 0;
	return (concat);
}
