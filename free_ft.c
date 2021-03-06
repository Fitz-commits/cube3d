/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:46:41 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/06 15:46:46 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_spec		*free_spec(t_spec *specs)
{
	free(specs);
	exit(0);
	return (NULL);
}

t_text		*free_spect(t_spec *specs)
{
	free(specs);
	exit(0);
	return (NULL);
}

t_spec		*free_line(char *line)
{
	free(line);
	return (NULL);
}

char		*free_line_char(char *line)
{
	free(line);
	return (NULL);
}

t_spec		*free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	return (NULL);
}
