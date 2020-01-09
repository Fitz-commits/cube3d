/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:47:22 by cdelaby           #+#    #+#             */
/*   Updated: 2019/12/12 14:22:03 by cdelaby          ###   ########.fr       */
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

int		main()
{
	void *mlx;
	void *win_ptr;
	t_spec *inf;

	inf = initSpec("./map.cub");
	mlx = mlx_init();
	win_ptr = mlx_new_window (mlx, 480, 270, "Projet du turfu" );

	double posX = 2, posY = 1; // Vecteur position
	double dirX = -1, dirY = 0; // Vecteur direction
	double planeX = 0, planeY = 0.66; // Vecteur plane

	double time = 0; // current time
	double oldTime = 0; //time of previous frame

	for(int x = 0; x < 270; x++)
    {
    	//calculate ray position and direction
    	double cameraX = 2 * x / (double)(270) - 1; //x-coordinate in camera space
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
	}
}