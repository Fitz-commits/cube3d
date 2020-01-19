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
char		*DrawInside(t_spec *inf, int *intimgptr, int drawStart, int drawEnd, int color, int x)
{
	int y;

	y = 0;
	while (y < drawStart)
		intimgptr[(y++ * inf->resX) + x] = 1689725;
	while (drawStart < drawEnd)
	{
		intimgptr[(drawStart * inf->resX) + x] = color;
		drawStart++;
	}
	while (drawEnd < inf->resY)
		intimgptr[(drawEnd++ * inf->resX) + x] = 16777085;
	return ((char*)intimgptr);
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

	//inf->imgptr = mlx_new_image(inf->mlx, inf->resX, inf->resY);
	//inf->charimgptr = mlx_get_data_addr(inf->imgptr, &l, &l, &l);
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
		int l;
		l = 0;
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + inf->resY / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + inf->resY / 2;
		if(drawEnd >= inf->resY)drawEnd = inf->resY - 1;


		// TEXTURES


		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = inf->posY + perpWallDist * rayDirY;
		else           wallX = inf->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)(inf->twidth));
		if(side == 0 && rayDirX > 0) texX = inf->twidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = inf->twidth - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * inf->theight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - inf->resY / 2 + lineHeight / 2) * step;
		int y;
		y = 0;
		while(y < drawStart)
			inf->intimgptr[(y++ * inf->resX) + x] = 1689725;
		for(y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (inf->theight - 1);
			texPos += step;
			int color = inf->ptrtext[inf->theight * texY + texX];
			inf->intimgptr[(y * inf->resX) + x] = color;
		}
		while (y < inf->resY)
			inf->intimgptr[(y++ * inf->resX) + x] = 1689725;







		//if (side == 0 && rayDirX > 0) inf->charimgptr = DrawInside(inf, (int*)inf->charimgptr, drawStart, drawEnd, 16777215, x); //blanc
		//if (side == 0 && rayDirX < 0) inf->charimgptr = DrawInside(inf, (int*)inf->charimgptr, drawStart, drawEnd, 16768000, x); //jaune
		//if (side == 1 && rayDirY < 0) inf->charimgptr = DrawInside(inf, (int*)inf->charimgptr, drawStart, drawEnd, 255, x); //bleu
		//if (side == 1 && rayDirY > 0) inf->charimgptr = DrawInside(inf, (int*)inf->charimgptr, drawStart, drawEnd, 16711680, x); //rouge

		/*if (side == 0 && rayDirX < 0) verLine(inf, drawStart, drawEnd, x, 16768000); //vert
		  if (side == 1 && rayDirY < 0) verLine(inf, drawStart, drawEnd, x, 255); // blue
		  if (side == 1 && rayDirY > 0) verLine(inf, drawStart, drawEnd, x, 16711680); // rouge*/
		//printf("drawStart = %d\ndrawStart = %d\n", drawStart, drawEnd);


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
	return (0);
}
int		main()
{
	t_spec *inf;
	int l;
	int i;

	l = 0;
	i = 0;
	inf = initSpec("./map.cub");
	inf->time = 0;
	inf->oldTime = 0;
	inf->mlx = mlx_init();
	inf->win_ptr = mlx_new_window (inf->mlx, inf->resX, inf->resY, "Projet du turfu" );
	inf->imgptr = mlx_new_image(inf->mlx, inf->resX, inf->resY);
	inf->charimgptr = mlx_get_data_addr(inf->imgptr, &l, &l, &l);
	inf->intimgptr = (int*)inf->charimgptr;
	inf->vtext1  = mlx_xpm_file_to_image(inf->mlx, "./text/redbrick.xpm", &inf->twidth, &inf->theight);
	inf->text1 = mlx_get_data_addr(inf->vtext1, &i, &i, &i);
	inf->ptrtext = (int*)inf->text1;
	draw(inf);
	mlx_hook(inf->win_ptr, 2, (1L << 0), key_hook, inf);
	mlx_hook(inf->win_ptr, 3, (1L << 1), key_hook, inf);
	//mlx_loop_hook(inf->mlx, draw, inf);
	//mlx_key_hook(inf->win_ptr, key_hook, (void*)inf);
	mlx_loop(inf->mlx);

}
