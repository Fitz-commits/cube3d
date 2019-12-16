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

int		main()
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
}
