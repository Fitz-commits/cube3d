/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 08:59:37 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/08 08:59:40 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *src)
{
	char *fin;

	fin = malloc(ft_strlen(src) + 1);
	if (fin == 0)
		return (0);
	ft_strcpy(fin, src);
	return (&*fin);
}
