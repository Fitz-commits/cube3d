/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:47:22 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/23 17:16:23 by cdelaby          ###   ########.fr       */
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
			if (inf->map[inf->map_x][inf->map_y] == '1') 
				hit = 1;
		}
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
	
}

void	dda_setup(t_spec *inf, int x)
{
	inf->camera_x = 2 * inf->x / (double)(inf->res_x) - 1;
	inf->ray_dir_x = inf->dir_x + inf->planeX * inf->camera_x;
	inf->ray_dir_y = inf->dir_y + inf->planeY * inf->camera_x;
	inf->map_x = (int)inf->pos_x;
	inf->map_y = (int)inf->pos_y;
	inf->delta_dist_x = fabs(1 / inf->ray_dir_x);
	inf->delta_dist_y = fabs(1 / inf->ray_dir_y);
	inf = set_side_step(inf);
	inf = perf_dda(inf);
	inf = set_draw(inf);
	inf = set_texture(inf);
	
}

int 	draw(t_spec *inf)
{
	double z_buffer[inf->res_x];


	inf->x = 0;
	while (inf->x < inf->res_x)
		//inf->imgptr = mlx_new_image(inf->mlx, inf->res_x, inf->res_y);
		//inf->charimgptr = mlx_get_data_addr(inf->imgptr, &l, &l, &l);
	{
		//calculate ray position and direction
		double cameraX = 2 * inf->x / (double)(inf->res_x) - 1 ; //x-coordinate in camera space
		double rayDirX = inf->dir_x + inf->planeX * cameraX;
		double rayDirY = inf->dir_y + inf->planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)(inf->pos_x);
		int mapY = (int)(inf->pos_y);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (inf->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - inf->pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (inf->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - inf->pos_y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (inf->map[mapY][mapX] == '1') 
				hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - inf->pos_x + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - inf->pos_y + (1 - stepY) / 2) / rayDirY;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(inf->res_y / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart =  -lineHeight / 2 + inf->res_y / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd =  lineHeight / 2 + inf->res_y / 2;
		if(drawEnd >= inf->res_y)drawEnd = inf->res_y - 1;

		// TEXTURES
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = inf->pos_y + perpWallDist * rayDirY;
		else           wallX = inf->pos_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		inf->texX = (int)(wallX * (double)(inf->text->twidth[0]));
		if(side == 0 && rayDirX > 0) inf->texX = inf->text->twidth[0] - inf->texX - 1;
		if(side == 1 && rayDirY < 0) inf->texX = inf->text->twidth[0] - inf->texX - 1;
		// How much to increase the texture coordinate per screen pixel
		inf->step = 1.0 * inf->text->theight[0] / lineHeight;
		// Starting texture coordinate
		inf->texPos = (drawStart - inf->res_y / 2 + lineHeight / 2) * inf->step;
		//need to implement draw inside
		if (side == 0 && rayDirX > 0) drawInside(inf, drawStart, drawEnd, 0);
		if (side == 0 && rayDirX < 0) drawInside(inf, drawStart, drawEnd, 1);
		if (side == 1 && rayDirY < 0) drawInside(inf, drawStart, drawEnd, 2);
		if (side == 1 && rayDirY > 0) drawInside(inf, drawStart, drawEnd, 3);
		z_buffer[inf->x] = perpWallDist;
		inf->x++;
	}
	inf->sprites = buble_sort_sprite(inf);
	for(int i = 0 ; i < inf->sprite_nb; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = inf->sprites->spriteX[i] - inf->pos_x;
		double spriteY = inf->sprites->spriteY[i] - inf->pos_y;

		double invDet = 1.0 / (inf->planeX * inf->dir_y - inf->dir_x * inf->planeY); //required for correct matrix multiplication

		double transformX = invDet * (inf->dir_y * spriteX - inf->dir_x * spriteY);
		double transformY = invDet * (-inf->planeY * spriteX + inf->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((inf->res_x / 2) * (1 + transformX / transformY));
		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(inf->res_y / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + inf->res_y / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + inf->res_y / 2;
		if(drawEndY >= inf->res_y) drawEndY = inf->res_y - 1;

//calculate width of the sprite
		int spriteWidth = abs( (int) (inf->res_y / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= inf->res_x) drawEndX = inf->res_x - 1;
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * inf->text->twidth[4] / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < inf->res_x && transformY < z_buffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - inf->res_y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * inf->text->theight[4]) / spriteHeight) / 256;
          int color = inf->text->itext[4][inf->text->twidth[4] * texY + texX]; //get current color from the texture
          if((color & 0x00FFFFFF) != 0) inf->intimgptr[(y * inf->res_x) + stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
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
		double oldPlaneX = inf->planeX;
		inf->planeX = inf->planeX * cos(-rotSpeed) - inf->planeY * sin(-rotSpeed);
		inf->planeY = oldPlaneX * sin(-rotSpeed) + inf->planeY * cos(-rotSpeed);
		//draw(inf);
	}
	if (key == K_RIGHT)
	{
		//mlx_clear_window ( inf->mlx, inf->win_ptr );
		//both camera direction and camera plane must be rotated
		double oldDirX = inf->dir_x;
		inf->dir_x = inf->dir_x * cos(rotSpeed) - inf->dir_y * sin(rotSpeed);
		inf->dir_y = oldDirX * sin(rotSpeed) + inf->dir_y * cos(rotSpeed);
		double oldPlaneX = inf->planeX;
		inf->planeX = inf->planeX * cos(rotSpeed) - inf->planeY * sin(rotSpeed);
		inf->planeY = oldPlaneX * sin(rotSpeed) + inf->planeY * cos(rotSpeed);
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

	l = 0;
	i = 0;
	inf = initSpec("./map.cub");
	inf->mlx = mlx_init();
	inf->win_ptr = mlx_new_window (inf->mlx, inf->res_x, inf->res_y, "Projet du turfu" );
	if (!(inf->text = init_void(inf)))
		return (0);
	inf->imgptr = mlx_new_image(inf->mlx, inf->res_x, inf->res_y);
	inf->charimgptr = mlx_get_data_addr(inf->imgptr, &l, &l, &l);
	inf->intimgptr = (int*)inf->charimgptr;
	//draw(inf);
	mlx_hook(inf->win_ptr, 2, (1L << 0), key_hook, inf);
	mlx_hook(inf->win_ptr, 3, (1L << 1), key_hook, inf);
	mlx_hook(inf->win_ptr, 17, 0, ft_close, inf);
	mlx_loop_hook(inf->mlx, draw, inf);
	mlx_loop(inf->mlx);
}
