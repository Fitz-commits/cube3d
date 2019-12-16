/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:48:41 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 14:41:38 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int index;

	index = -1;
	i = 0;
	while (s[i] != 0)
	{
		if (c == s[i])
			index = i;
		i++;
	}
	if (c == 0)
		return ((char*)&s[i]);
	if (index != -1)
		return ((char*)&s[index]);
	return (0);
}
