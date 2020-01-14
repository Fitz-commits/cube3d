/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:47:22 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/14 17:29:07 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "mlx.h"
#include <stdio.h>
#include "math.h"
#include "cube3d.h"

/*int		main()
  {
  void *mlx;
  void *win_ptr;
  int i;
  int j = 200;
  i = 200;
  mlx = mlx_init();
  win_ptr = mlx_new_window (mlx, 1920, 1080, "hello" );
  while (j < 500)
  {
  i = 200;
  while(i < 600)
  mlx_pixel_put (mlx, win_ptr, i++, j, 16777215);
  j++;
  }
  mlx_loop(mlx);
  return (0);
  }*/

int 	draw(t_spec *inf)
{
	for(int x = 0; x < inf->resX; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(inf->resX) - 1 ; //x-coordinate in camera space
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

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + inf->resY / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + inf->resY / 2;
		if(drawEnd >= inf->resY)drawEnd = inf->resY - 1;
		//printf("drawStart = %d\ndrawStart = %d\n", drawStart, drawEnd);
		printf("drawstart = %d\ndrawEnd = %d\nx = %d \n", drawStart, drawEnd, x);
		verLine(inf, drawStart, drawEnd, x);
	}
	return (1);
}
int		verLine(t_spec *inf, int draw_start, int draw_end, int x)
{
	while(draw_start < draw_end)
	{
		mlx_pixel_put (inf->mlx, inf->win_ptr, x, draw_start++, 16777215);
	}
	return (1);
}
int		key_hook(int key,void *param)
  {
  t_spec *inf;

  inf = (t_spec*)param;
  if (key == K_W)
  {
		mlx_clear_window ( inf->mlx, inf->win_ptr );
		if(inf->map[(int)(inf->posY)][(int)(inf->posX + inf->dirX * moveSpeed)] == '0') inf->posX += inf->dirX * moveSpeed;
      	if(inf->map[(int)(inf->posY + inf->dirY * moveSpeed)][(int)inf->posX] == '0') inf->posY += inf->dirY * moveSpeed;
		draw(inf);
  }
  if (key == K_S)
  {
		mlx_clear_window ( inf->mlx, inf->win_ptr );
		if(inf->map[(int)(inf->posY)][(int)(inf->posX - inf->dirX * moveSpeed)] == '0') inf->posX -= inf->dirX * moveSpeed;
      	if(inf->map[(int)(inf->posY - inf->dirY * moveSpeed)][(int)inf->posX] == '0') inf->posY -= inf->dirY * moveSpeed;
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
  printf("%d\n", key);
  return (0);
  }
int		main()
{
	t_spec *inf;

	inf = initSpec("./map.cub");
	inf->mlx = mlx_init();
	inf->win_ptr = mlx_new_window (inf->mlx, inf->resX, inf->resY, "Projet du turfu" );
	draw(inf);
	mlx_key_hook(inf->win_ptr, key_hook, (void*)inf);
	mlx_loop(inf->mlx);
}

