/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:47:22 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/19 10:46:06 by cdelaby          ###   ########.fr       */
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
			inf->intimgptr[(y++ * inf->resX) + inf->x] = inf->colorC;
		while (y < drawEnd)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)inf->texPos & (inf->text->theight[texNum] - 1);
			inf->texPos += inf->step;
			int color = inf->text->itext[texNum][inf->text->theight[texNum] * texY + inf->texX];
			inf->intimgptr[(y++ * inf->resX) + inf->x] = color;
		}
		while (y < inf->resY)
			inf->intimgptr[(y++ * inf->resX) + inf->x] = inf->colorF;
}
char *clearImage(t_spec *inf)
{
	int x;
	x = 0;
	int *intimgptr;
	intimgptr = (int*)inf->charimgptr;
	while (x < inf->resX*inf->resY)
		intimgptr[x++] = 0;
	return (NULL);
}
int 	draw(t_spec *inf)
{
	inf->x = 0;
	while (inf->x < inf->resX)
	//inf->imgptr = mlx_new_image(inf->mlx, inf->resX, inf->resY);
	//inf->charimgptr = mlx_get_data_addr(inf->imgptr, &l, &l, &l);
	{
		//calculate ray position and direction
		double cameraX = 2 * inf->x / (double)(inf->resX) - 1 ; //x-coordinate in camera space
		double rayDirX = inf->dirX + inf->planeX * cameraX;
		double rayDirY = inf->dirY + inf->planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)(inf->posX);
		int mapY = (int)(inf->posY);

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
			sideDistX = (inf->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - inf->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (inf->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - inf->posY) * deltaDistY;
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
		if(side == 0) perpWallDist = (mapX - inf->posX + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - inf->posY + (1 - stepY) / 2) / rayDirY;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(inf->resY / perpWallDist);
		int l;
		l = 0;
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart =  -lineHeight / 2 + inf->resY / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd =  lineHeight / 2 + inf->resY / 2;
		if(drawEnd >= inf->resY)drawEnd = inf->resY - 1;
		// TEXTURES
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = inf->posY + perpWallDist * rayDirY;
		else           wallX = inf->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		inf->texX = (int)(wallX * (double)(inf->text->twidth[0]));
		if(side == 0 && rayDirX > 0) inf->texX = inf->text->twidth[0] - inf->texX - 1;
		if(side == 1 && rayDirY < 0) inf->texX = inf->text->twidth[0] - inf->texX - 1;
		// How much to increase the texture coordinate per screen pixel
		inf->step = 1.0 * inf->text->theight[0] / lineHeight;
		// Starting texture coordinate
		inf->texPos = (drawStart - inf->resY / 2 + lineHeight / 2) * inf->step;
		//need to implement draw inside
		if (side == 0 && rayDirX > 0) drawInside(inf, drawStart, drawEnd, 0);
		if (side == 0 && rayDirX < 0) drawInside(inf, drawStart, drawEnd, 1);
		if (side == 1 && rayDirY < 0) drawInside(inf, drawStart, drawEnd, 2);
		if (side == 1 && rayDirY > 0) drawInside(inf, drawStart, drawEnd, 3);
	inf->z_buffer[inf->x] = perpWallDist;
	inf->x++;
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
		mlx_clear_window ( inf->mlx, inf->win_ptr);
		if(inf->map[(int)(inf->posY)][(int)(inf->posX + inf->dirX * moveSpeed)] != '1') 
			inf->posX += inf->dirX * moveSpeed;
		if(inf->map[(int)(inf->posY + inf->dirY * moveSpeed + (inf->dirY < 0 ? -0.20 : 0.20))][(int)inf->posX] != '1') 
			inf->posY += inf->dirY * moveSpeed;
		draw(inf);
	}
	if (key == K_D)
	{
		mlx_clear_window ( inf->mlx, inf->win_ptr);
		if(inf->map[(int)(inf->posY)][(int)(inf->posX + -inf->dirY * moveSpeed + (-inf->dirY < 0 ? -0.20 : 0.20))] != '1') 
			inf->posX += -inf->dirY * moveSpeed;
		if(inf->map[(int)(inf->posY + inf->dirY * moveSpeed + (inf->dirX < 0 ? -0.20 : 0.20))][(int)inf->posX] != '1') 
			inf->posY += inf->dirX * moveSpeed;
		draw(inf);
	}
	if (key == K_A)
	{
		mlx_clear_window ( inf->mlx, inf->win_ptr);
		if(inf->map[(int)(inf->posY)][(int)(inf->posX + inf->dirY * moveSpeed + (inf->dirY < 0 ? -0.20 : 0.20))] != '1') 
			inf->posX += inf->dirY * moveSpeed;
		if(inf->map[(int)(inf->posY + inf->dirY * moveSpeed + (-inf->dirX < 0 ? -0.20 : 0.20))][(int)inf->posX] != '1') 
			inf->posY += -inf->dirX * moveSpeed;
		draw(inf);
	}
	if (key == K_S)
	{
		mlx_clear_window ( inf->mlx, inf->win_ptr );
		if(inf->map[(int)(inf->posY)][(int)(inf->posX - inf->dirX * moveSpeed)] != '1') inf->posX -= inf->dirX * moveSpeed;
		if(inf->map[(int)(inf->posY - inf->dirY * moveSpeed)][(int)inf->posX] != '1') inf->posY -= inf->dirY * moveSpeed;
		draw(inf);
	}
	if (key == K_LEFT)
	{
		mlx_clear_window ( inf->mlx, inf->win_ptr );
		//both camera direction and camera plane must be rotated
		double oldDirX = inf->dirX;
		inf->dirX = inf->dirX * cos(-rotSpeed) - inf->dirY * sin(-rotSpeed);
		inf->dirY = oldDirX * sin(-rotSpeed) + inf->dirY * cos(-rotSpeed); 
		double oldPlaneX = inf->planeX;
		inf->planeX = inf->planeX * cos(-rotSpeed) - inf->planeY * sin(-rotSpeed);
		inf->planeY = oldPlaneX * sin(-rotSpeed) + inf->planeY * cos(-rotSpeed);
		draw(inf);
	}
	if (key == K_RIGHT)
	{
		mlx_clear_window ( inf->mlx, inf->win_ptr );
		//both camera direction and camera plane must be rotated
		double oldDirX = inf->dirX;
		inf->dirX = inf->dirX * cos(rotSpeed) - inf->dirY * sin(rotSpeed);
		inf->dirY = oldDirX * sin(rotSpeed) + inf->dirY * cos(rotSpeed);
		double oldPlaneX = inf->planeX;
		inf->planeX = inf->planeX * cos(rotSpeed) - inf->planeY * sin(rotSpeed);
		inf->planeY = oldPlaneX * sin(rotSpeed) + inf->planeY * cos(rotSpeed);
		draw(inf);
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
int		ft_close(t_spec inf)
{
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
	inf->z_buffer = malloc(sizeof(double) * inf->resX);
	inf->mlx = mlx_init();
	inf->win_ptr = mlx_new_window (inf->mlx, inf->resX, inf->resY, "Projet du turfu" );
	if (!(inf->text = init_void(inf)))
        return (0);
	inf->imgptr = mlx_new_image(inf->mlx, inf->resX, inf->resY);
	inf->charimgptr = mlx_get_data_addr(inf->imgptr, &l, &l, &l);
	inf->intimgptr = (int*)inf->charimgptr;
	draw(inf);
	mlx_hook(inf->win_ptr, 2, (1L << 0), key_hook, inf);
	mlx_hook(inf->win_ptr, 3, (1L << 1), key_hook, inf);
	mlx_hook(inf->win_ptr, 17, 0, ft_close, inf);
	//mlx_loop_hook(inf->mlx, draw, inf);
	mlx_loop(inf->mlx);
}
