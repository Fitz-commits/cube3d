/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:25:50 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/16 15:04:06 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*subs;
	unsigned int		i;

	if (s == 0)
		return (NULL);
	if (len > (unsigned)ft_strlen(s) || start > (unsigned)ft_strlen(s))
		return (ft_strdup(""));
	if (!(subs = malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len && s[i + start])
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = 0;
	return (subs);
}
