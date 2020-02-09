/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:04:38 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 18:04:39 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

double			*cacl_dist(t_spec *inf)
{
	double		*dist;
	int			i;

	i = -1;
	if (!(dist = (double*)malloc(sizeof(double) * inf->sprite_nb)))
		return (NULL);
	while (++i < inf->sprite_nb)
		dist[i] = (inf->pos_x - inf->sprites->sprite_x[i])
			* (inf->pos_x - inf->sprites->sprite_x[i])
			+ (inf->pos_y - inf->sprites->sprite_y[i]) *
			(inf->pos_y - inf->sprites->sprite_y[i]);
	return (dist);
}

void			swap_sprite(t_spec *inf, int i, int j)
{
	double temp_x;
	double temp_y;

	temp_x = inf->sprites->sprite_x[i];
	temp_y = inf->sprites->sprite_y[i];
	inf->sprites->sprite_x[i] = inf->sprites->sprite_x[j];
	inf->sprites->sprite_y[i] = inf->sprites->sprite_y[j];
	inf->sprites->sprite_x[j] = temp_x;
	inf->sprites->sprite_y[j] = temp_y;
}

t_sprite		*buble_sort_sprite(t_spec *inf)
{
	int		i;
	int		j;
	double	tempdist;
	double	*dist;

	i = -1;
	j = -1;
	if (!(dist = cacl_dist(inf)))
		return (0);
	while (++i < inf->sprite_nb - 1)
		while (++j < inf->sprite_nb - i - 1)
			if (dist[j] < dist[j + 1])
			{
				swap_sprite(inf, j, j + 1);
				tempdist = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = dist[j];
			}
	free(dist);
	return (inf->sprites);
}
