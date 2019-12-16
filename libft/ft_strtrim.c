/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:11 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 16:19:15 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	char			*trim;
	unsigned int	start;
	int				size;

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	size = ft_strlen(&s1[start]);
	if (size)
		while (s1[start + size - 1] && ft_strchr(set, s1[start + size - 1]))
			size--;
	if (!(trim = malloc(sizeof(char) * (size + 1))))
		return (0);
	trim = ft_strncpy(trim, &s1[start], size);
	trim[size] = 0;
	return (trim);
}
