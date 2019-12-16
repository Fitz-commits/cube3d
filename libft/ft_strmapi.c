/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:33:08 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/09 16:37:41 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*t;
	int				len;
	unsigned int	i;

	i = 0;
	if (s == 0 || (*f) == 0)
		return (0);
	len = ft_strlen(s);
	if (!(t = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (s[i])
	{
		t[i] = (char)((*f)(i, s[i]));
		i++;
	}
	t[i] = 0;
	return (t);
}
