/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 08:16:51 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 19:31:10 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int				ft_ar_to_int(char *color)
{
	int r;
	int g;
	int b;
	int colorhex;

	r = ft_atoi(color);
	g = ft_atoi(&color[get_size(r, 10) + 1]);
	b = ft_atoi(&color[get_size(r, 10) + get_size(g, 10) + 2]);
	colorhex = r * 256 * 256 + g * 256 + b;
	return (colorhex);
}

void			rotate_left(t_spec *inf)
{
	double old_plane_x;
	double old_dir_x;

	old_dir_x = inf->dir_x;
	inf->dir_x = inf->dir_x * cos(-ROTSPEED) - inf->dir_y * sin(-ROTSPEED);
	inf->dir_y = old_dir_x * sin(-ROTSPEED) + inf->dir_y * cos(-ROTSPEED);
	old_plane_x = inf->plane_x;
	inf->plane_x = inf->plane_x * cos(-ROTSPEED) -
		inf->plane_y * sin(-ROTSPEED);
	inf->plane_y = old_plane_x * sin(-ROTSPEED) + inf->plane_y * cos(-ROTSPEED);
	inf->up->key_left = 0;
}

void			rotate_right(t_spec *inf)
{
	double old_plane_x;
	double old_dir_x;

	old_dir_x = inf->dir_x;
	inf->dir_x = inf->dir_x * cos(ROTSPEED) - inf->dir_y * sin(ROTSPEED);
	inf->dir_y = old_dir_x * sin(ROTSPEED) + inf->dir_y * cos(ROTSPEED);
	old_plane_x = inf->plane_x;
	inf->plane_x = inf->plane_x * cos(ROTSPEED) - inf->plane_y * sin(ROTSPEED);
	inf->plane_y = old_plane_x * sin(ROTSPEED) + inf->plane_y * cos(ROTSPEED);
	inf->up->key_right = 0;
}

int				is_space(char c)
{
	if (c == '\t' || c == '\r' || c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}
