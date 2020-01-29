/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:47:22 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/28 19:36:17 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "mlx.h"
#include <stdio.h>
#include "math.h"
#include "cube3d.h"
#include <time.h>


void		drawInside(t_spec *inf, int drawStart, int drawEnd, int texNum)
{
	int y;
	y = 0;
	while(y <= drawStart)
		inf->intimgptr[(y++ * inf->res_x) + inf->x] = inf->colorC;
	while (y < drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)inf->texPos & (inf->text->theight[texNum] - 1);
		inf->texPos += inf->step;
		int color = inf->text->itext[texNum][inf->text->theight[texNum] * texY + inf->texX];
		inf->intimgptr[(y++ * inf->res_x) + inf->x] = color;
	}
	while (y < inf->res_y)
		inf->intimgptr[(y++ * inf->res_x) + inf->x] = inf->colorF;
}
t_spec	*set_side_step(t_spec *inf)
{
	if (inf->ray_dir_x < 0)
	{
		inf->step_x = -1;
		inf->side_dist_x = (inf->pos_x - inf->map_x) * inf->delta_dist_x;
	}
	else
	{
		inf->step_x = 1;
		inf->side_dist_x = (inf->map_x + 1.0 -inf->pos_x) * inf->delta_dist_x;
	}
	if (inf->ray_dir_y < 0)
	{
		inf->step_y = -1;
		inf->side_dist_y = (inf->pos_y - inf->map_y) * inf->delta_dist_y;
	}
	else
	{
		inf->step_y = 1;
		inf->side_dist_y = (inf->map_y + 1.0 -inf->pos_y) * inf->delta_dist_y;
	}
	return (inf);
}
t_spec		*perf_dda(t_spec *inf)
{	
	int hit;

	hit = 0;
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (inf->side_dist_x<  inf->side_dist_y)
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
		//Check if ray has hit a wall
		if (inf->map[inf->map_y][inf->map_x] == '1') 
			hit = 1;
	}
	return (inf);
}

t_spec		*set_draw(t_spec *inf)
{
	if (inf->side == 0)
		inf->perp_wall_dist = (inf->map_x - inf->pos_x + (1 - inf->step_x) /
				2) / inf->ray_dir_x;
	else
		inf->perp_wall_dist = (inf->map_y - inf->pos_y + (1 - inf->step_y) /
				2) / inf->ray_dir_y;
	inf->line_height = (int)(inf->res_y / inf->perp_wall_dist);
	inf->draw_start = -inf->line_height / 2 + inf->res_y/2;
	if (inf->draw_start < 0)
		inf->draw_start = 0;
	inf->draw_end = inf->line_height /2 + inf->res_y / 2;
	if (inf->draw_end >= inf->res_y)
		inf->draw_end = inf->res_y - 1;
	if (inf->side == 0) 
		inf->wall_x = inf->pos_y + inf->perp_wall_dist * inf->ray_dir_y;
	else
		inf->wall_x = inf->pos_x + inf->perp_wall_dist * inf->ray_dir_x;
	inf->wall_x -= floor((inf->wall_x));
	return (inf);
}
t_spec		*set_texture(t_spec *inf)
{
	inf->texX = (int)(inf->wall_x * (double)(inf->text->twidth[0]));
	if(inf->side == 0 && inf->ray_dir_x > 0)
		inf->texX = inf->text->twidth[0] - inf->texX - 1;
	if(inf->side == 1 && inf->ray_dir_y < 0)
		inf->texX = inf->text->twidth[0] - inf->texX - 1;
	inf->step = 1.0 * inf->text->theight[0] / inf->line_height;
	inf->texPos = (inf->draw_start - inf->res_y / 2 +
			inf->line_height / 2) * inf->step;
	return (inf);
}

void	dda_setup(t_spec *inf)
{
	inf->camera_x = 2 * inf->x / (double)(inf->res_x) - 1;
	inf->ray_dir_x = inf->dir_x + inf->plane_x * inf->camera_x;
	inf->ray_dir_y = inf->dir_y + inf->plane_y * inf->camera_x;
	inf->map_x = (int)inf->pos_x;
	inf->map_y = (int)inf->pos_y;
	inf->delta_dist_x = fabs(1 / inf->ray_dir_x);
	inf->delta_dist_y = fabs(1 / inf->ray_dir_y);
	inf = set_side_step(inf);
	inf = perf_dda(inf);
	inf = set_draw(inf);
	inf = set_texture(inf);
}
void sprite_math(t_spec *inf, int i)
{
	inf->sprite_x = inf->sprites->sprite_x[i] - inf->pos_x;
	inf->sprite_y = inf->sprites->sprite_y[i] - inf->pos_y;
	inf->inv_det = 1.0 / (inf->plane_x * inf->dir_y - inf->dir_x * inf->plane_y);
	inf->trans_x = inf->inv_det * (inf->dir_y * inf->sprite_x -
			inf->dir_x * inf->sprite_y);
	inf->trans_y = inf->inv_det * (-inf->plane_y * inf->sprite_x +
			inf->plane_x * inf->sprite_y);
	inf->sprite_screen_x = (int)((inf->res_x / 2) * (1 + inf->trans_x / inf->trans_y));
	inf->sprite_height = abs((int)(inf->res_y / (inf->trans_y)));
	inf->draw_start_y = -inf->sprite_height / 2 + inf->res_y / 2;
	if (inf->draw_start_y < 0)
		inf->draw_start_y = 0;
	inf->draw_end_y = inf->sprite_height / 2 + inf->res_y / 2;
	if (inf->draw_end_y >= inf->res_y)
		inf->draw_end_y = inf->res_y - 1;
	inf->sprite_width = abs((int)(inf->res_y / (inf->trans_y)));
	inf->draw_start_x = -inf->sprite_width / 2 + inf->sprite_screen_x;
	if(inf->draw_start_x < 0)
		inf->draw_start_x = 0;
	inf->draw_end_x = inf->sprite_width / 2 + inf->sprite_screen_x;
	if(inf->draw_end_x >= inf->res_x)
		inf->draw_end_x = inf->res_x - 1;
}

void sprite_setup(t_spec *inf, int i)
{
	sprite_math(inf, i);
}

int 	draw(t_spec *inf)
{
	double z_buffer[inf->res_x];
	int i;

	inf->x = 0;
	while (inf->x < inf->res_x)
	{
		dda_setup(inf);
		if (inf->side == 0 && inf->ray_dir_x > 0) drawInside(inf, inf->draw_start,inf->draw_end, 0);
		if (inf->side == 0 && inf->ray_dir_x < 0) drawInside(inf, inf->draw_start,inf->draw_end, 1);
		if (inf->side == 1 && inf->ray_dir_y < 0) drawInside(inf, inf->draw_start,inf->draw_end, 2);
		if (inf->side == 1 && inf->ray_dir_y > 0) drawInside(inf, inf->draw_start,inf->draw_end, 3);
		z_buffer[inf->x] = inf->perp_wall_dist;
		inf->x++;
	}
	inf->sprites = buble_sort_sprite(inf);
	i = 0;
	while (i < inf->sprite_nb)
	{
		sprite_math(inf, i);
		for(int stripe = inf->draw_start_x; stripe < inf->draw_end_x; stripe++)
		{
			int texX = (int)(256 * (stripe - (-inf->sprite_width / 2 + inf->sprite_screen_x)) * inf->text->twidth[4] / inf->sprite_width) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(inf->trans_y > 0 && stripe > 0 && stripe < inf->res_x && inf->trans_y < z_buffer[stripe])
				for(int y = inf->draw_start_y; y < inf->draw_end_y; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - inf->res_y * 128 + inf->sprite_height * 128; //256 and 128 factors to avoid floats
					int texY = ((d * inf->text->theight[4]) / inf->sprite_height) / 256;
					int color = inf->text->itext[4][inf->text->twidth[4] * texY + texX]; //get current color from the texture
					if((color & 0x00FFFFFF) != 0) inf->intimgptr[(y * inf->res_x) + stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
		}
		i++;
	}
	mlx_put_image_to_window (inf->mlx, inf->win_ptr, inf->imgptr, 0, 0);
	//clearImage(inf);
	return (1);
}

int		key_hook(int key,void *param)
{
	t_spec *inf;

	inf = (t_spec*)param;
	if (key == K_W)
	{
		//mlx_clear_window ( inf->mlx, inf->win_ptr);
		if(inf->map[(int)(inf->pos_y)][(int)(inf->pos_x + inf->dir_x * moveSpeed)] != '1') 
			inf->pos_x += inf->dir_x * moveSpeed;
		if(inf->map[(int)(inf->pos_y + inf->dir_y * moveSpeed + (inf->dir_y < 0 ? -0.20 : 0.20))][(int)inf->pos_x] != '1') 
			inf->pos_y += inf->dir_y * moveSpeed;
		//draw(inf);
	}
	if (key == K_D)
	{
		//mlx_clear_window ( inf->mlx, inf->win_ptr);
		if(inf->map[(int)(inf->pos_y)][(int)(inf->pos_x + -inf->dir_y * moveSpeed + (-inf->dir_y < 0 ? -0.20 : 0.20))] != '1') 
			inf->pos_x += -inf->dir_y * moveSpeed;
		if(inf->map[(int)(inf->pos_y + inf->dir_y * moveSpeed + (inf->dir_x < 0 ? -0.20 : 0.20))][(int)inf->pos_x] != '1') 
			inf->pos_y += inf->dir_x * moveSpeed;
		//draw(inf);
	}
	if (key == K_A)
	{
		//mlx_clear_window ( inf->mlx, inf->win_ptr);
		if(inf->map[(int)(inf->pos_y)][(int)(inf->pos_x + inf->dir_y * moveSpeed + (inf->dir_y < 0 ? -0.20 : 0.20))] != '1') 
			inf->pos_x += inf->dir_y * moveSpeed;
		if(inf->map[(int)(inf->pos_y + inf->dir_y * moveSpeed + (-inf->dir_x < 0 ? -0.20 : 0.20))][(int)inf->pos_x] != '1') 
			inf->pos_y += -inf->dir_x * moveSpeed;
		//draw(inf);
	}
	if (key == K_S)
	{
		//mlx_clear_window ( inf->mlx, inf->win_ptr );
		if(inf->map[(int)(inf->pos_y)][(int)(inf->pos_x - inf->dir_x * moveSpeed)] != '1') inf->pos_x -= inf->dir_x * moveSpeed;
		if(inf->map[(int)(inf->pos_y - inf->dir_y * moveSpeed)][(int)inf->pos_x] != '1') inf->pos_y -= inf->dir_y * moveSpeed;
		//draw(inf);
	}
	if (key == K_LEFT)
	{
		//mlx_clear_window ( inf->mlx, inf->win_ptr );
		//both camera direction and camera plane must be rotated
		double oldDirX = inf->dir_x;
		inf->dir_x = inf->dir_x * cos(-rotSpeed) - inf->dir_y * sin(-rotSpeed);
		inf->dir_y = oldDirX * sin(-rotSpeed) + inf->dir_y * cos(-rotSpeed); 
		double oldPlaneX = inf->plane_x;
		inf->plane_x = inf->plane_x * cos(-rotSpeed) - inf->plane_y * sin(-rotSpeed);
		inf->plane_y = oldPlaneX * sin(-rotSpeed) + inf->plane_y * cos(-rotSpeed);
		//draw(inf);
	}
	if (key == K_RIGHT)
	{
		//mlx_clear_window ( inf->mlx, inf->win_ptr );
		//both camera direction and camera plane must be rotated
		double oldDirX = inf->dir_x;
		inf->dir_x = inf->dir_x * cos(rotSpeed) - inf->dir_y * sin(rotSpeed);
		inf->dir_y = oldDirX * sin(rotSpeed) + inf->dir_y * cos(rotSpeed);
		double oldPlaneX = inf->plane_x;
		inf->plane_x = inf->plane_x * cos(rotSpeed) - inf->plane_y * sin(rotSpeed);
		inf->plane_y = oldPlaneX * sin(rotSpeed) + inf->plane_y * cos(rotSpeed);
		//draw(inf);
	}
	if (key == K_ESC)
	{
		mlx_destroy_window(inf->mlx, inf->win_ptr);
		exit(0);
	}
	if (key == 17)
	{
		mlx_destroy_window(inf->mlx, inf->win_ptr);
		exit(0);
	}
	return (0);
}
int		ft_close(t_spec *inf)
{
	inf = NULL;
	exit(0);
}
int		main()
{
	t_spec *inf;
	int l;
	int i;
	int j;
	int k;

	l = 0;
	i = 0;
	inf = initSpec("./map.cub");
	inf->mlx = mlx_init();
	inf->win_ptr = mlx_new_window (inf->mlx, inf->res_x, inf->res_y, "Projet du turfu" );
	if (!(inf->text = init_void(inf)))
		return (0);
	inf->imgptr = mlx_new_image(inf->mlx, inf->res_x, inf->res_y);
	inf->charimgptr = mlx_get_data_addr(inf->imgptr, &j, &k, &l);
	inf->intimgptr = (int*)inf->charimgptr;
	draw(inf);
	save_bmp(inf);
	mlx_hook(inf->win_ptr, 2, (1L << 0), key_hook, inf);
	mlx_hook(inf->win_ptr, 3, (1L << 1), key_hook, inf);
	mlx_hook(inf->win_ptr, 17, 0, ft_close, inf);
	mlx_loop_hook(inf->mlx, draw, inf);
	mlx_loop(inf->mlx);
}
