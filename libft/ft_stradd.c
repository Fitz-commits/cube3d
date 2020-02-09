/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:34:25 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/27 13:44:42 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_stradd(char *rest, char *s2)
{
	char			*copy;
	char			*copy_cpp;
	char			*rest_cpp;

	if (rest == NULL)
		return (ft_strdup(s2));
	copy = ft_strdup(rest);
	free(rest);
	copy_cpp = copy;
	if (!(rest = (char*)malloc(sizeof(char) * (ft_strlen(copy)
						+ ft_strlen(s2) + 1))))
		return (0);
	rest_cpp = rest;
	while (*copy)
		*rest++ = *copy++;
	while (*s2)
		*rest++ = *s2++;
	free(copy_cpp);
	*rest = 0;
	return (rest_cpp);
}
