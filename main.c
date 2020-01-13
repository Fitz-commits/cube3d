/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:47:22 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/13 09:37:41 by cdelaby          ###   ########.fr       */
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
int		verLine( void *mlx, void *win_ptr, int draw_start, int draw_end, int x)
{
	while(draw_start < draw_end)
	{
		mlx_pixel_put (mlx, win_ptr, x, draw_start++, 16777215);
	}
	return (1);
}
int		key_hook(int keycode,void *param)
{
	printf("%d", keycode);
	return (0);
}
int		main()
{
	void *mlx;
	void *win_ptr;
	t_spec *inf;

	inf = initSpec("./map.cub");
	mlx = mlx_init();
	win_ptr = mlx_new_window (mlx, inf->resX, inf->resY, "Projet du turfu" );
	inf = initSpec("./map.cub");

	double posX = 6.5, posY = 3.5; // x and y position
	double dirX = 0, dirY = 1; // Vecteur direction
	double planeX = 0.66, planeY = 0; // Vecteur plane --> || 9/11

	int done = 0;
		for(int x = 0; x < inf->resX; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double)(inf->resX) - 1 ; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			//which box of the map we're in
			int mapX = (int)(posX);
			int mapY = (int)(posY);

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
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
				{
					printf("map x = %d\nmap y = %d\nstepY = %d\nperpWallDist=%f", mapX, mapY, stepY, (mapY - posY + (1 - stepY) / 2) / rayDirY);
					hit = 1;
				}
			}

			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
			//Calculate height of line to draw on screen
			int lineHeight = (int)(inf->resY / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + inf->resY / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + inf->resY / 2;
			if(drawEnd >= inf->resY)drawEnd = inf->resY - 1;
			//printf("drawStart = %d\ndrawStart = %d\n", drawStart, drawEnd);
			printf("drawstart = %d\ndrawEnd = %d\nx = %d \n", drawStart, drawEnd, x);
			verLine(mlx, win_ptr, drawStart, drawEnd, x);
		}
		mlx_key_hook ( win_ptr, (key_hook)(keycode, param), param);
		mlx_loop(mlx);
	}

