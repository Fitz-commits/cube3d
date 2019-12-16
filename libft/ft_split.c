/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:30:29 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/15 09:24:49 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			count(char const *str, char c)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue;
		}
		j++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (j);
}

static char			**itsfree(char **split, int j)
{
	while (j >= 0)
	{
		ft_bzero((void*)split[j], ft_strlen(split[j]));
		free(split[j]);
		j--;
	}
	free(split);
	return (NULL);
}

char				**ft_split(char const *str, char c)
{
	size_t		j;
	size_t		k;
	char		**split;

	j = 0;
	if (str == 0)
		return (0);
	if (!(split = (char**)malloc(sizeof(char*) * (count(str, c) + 1))))
		return (0);
	while (*str)
	{
		if (*str == c)
		{
			str++;
			continue;
		}
		k = 0;
		while (str[k] && str[k] != c)
			k++;
		if ((split[j++] = ft_strndup(str, k)) == NULL)
			return (itsfree(split, j));
		str += k;
	}
	split[j] = 0;
	return (split);
}
