/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:53:46 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 17:53:48 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void			set_side_step(t_spec *inf)
{
	if (inf->ray_dir_x < 0)
	{
		inf->step_x = -1;
		inf->side_dist_x = (inf->pos_x - inf->map_x) * inf->delta_dist_x;
	}
	else
	{
		inf->step_x = 1;
		inf->side_dist_x = (inf->map_x + 1.0 - inf->pos_x) * inf->delta_dist_x;
	}
	if (inf->ray_dir_y < 0)
	{
		inf->step_y = -1;
		inf->side_dist_y = (inf->pos_y - inf->map_y) * inf->delta_dist_y;
	}
	else
	{
		inf->step_y = 1;
		inf->side_dist_y = (inf->map_y + 1.0 - inf->pos_y) * inf->delta_dist_y;
	}
}

void			perf_dda(t_spec *inf)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (inf->side_dist_x < inf->side_dist_y)
		{
			inf->side_dist_x += inf->delta_dist_x;
			inf->map_x += inf->step_x;
			inf->side = 0;
		}
		else
		{
			inf->side_dist_y += inf->delta_dist_y;
			inf->map_y += inf->step_y;
			inf->side = 1;
		}
		if (inf->map[inf->map_y][inf->map_x] == '1')
			hit = 1;
	}
}

void			set_draw(t_spec *inf)
{
	if (inf->side == 0)
		inf->perp_wall_dist = (inf->map_x - inf->pos_x + (1 - inf->step_x) /
				2) / inf->ray_dir_x;
	else
		inf->perp_wall_dist = (inf->map_y - inf->pos_y + (1 - inf->step_y) /
				2) / inf->ray_dir_y;
	inf->line_height = (int)(inf->res_y / inf->perp_wall_dist);
	inf->draw_start = -inf->line_height / 2 + inf->res_y / 2;
	if (inf->draw_start < 0)
		inf->draw_start = 0;
	inf->draw_end = inf->line_height / 2 + inf->res_y / 2;
	if (inf->draw_end >= inf->res_y)
		inf->draw_end = inf->res_y - 1;
	if (inf->side == 0)
		inf->wall_x = inf->pos_y + inf->perp_wall_dist * inf->ray_dir_y;
	else
		inf->wall_x = inf->pos_x + inf->perp_wall_dist * inf->ray_dir_x;
	inf->wall_x -= floor((inf->wall_x));
}

void			put_pixel_img(t_spec *inf, double *zbuf)
{
	dda_setup(inf);
	if (inf->side == 0 && inf->ray_dir_x > 0)
		draw_inside(inf, inf->draw_start, inf->draw_end, 0);
	if (inf->side == 0 && inf->ray_dir_x < 0)
		draw_inside(inf, inf->draw_start, inf->draw_end, 1);
	if (inf->side == 1 && inf->ray_dir_y < 0)
		draw_inside(inf, inf->draw_start, inf->draw_end, 2);
	if (inf->side == 1 && inf->ray_dir_y > 0)
		draw_inside(inf, inf->draw_start, inf->draw_end, 3);
	zbuf[inf->x] = inf->perp_wall_dist;
	inf->x++;
}

void			dda_setup(t_spec *inf)
{
	inf->camera_x = 2 * inf->x / (double)(inf->res_x) - 1;
	inf->ray_dir_x = inf->dir_x + inf->plane_x * inf->camera_x;
	inf->ray_dir_y = inf->dir_y + inf->plane_y * inf->camera_x;
	inf->map_x = (int)inf->pos_x;
	inf->map_y = (int)inf->pos_y;
	inf->delta_dist_x = fabs(1 / inf->ray_dir_x);
	inf->delta_dist_y = fabs(1 / inf->ray_dir_y);
	set_side_step(inf);
	perf_dda(inf);
	set_draw(inf);
	set_texture(inf);
}
