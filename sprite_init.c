/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:05:37 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 19:40:54 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int				get_sprite_number(char **map)
{
	int i;
	int j;
	int nb;

	i = -1;
	j = -1;
	nb = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == '2')
				nb++;
	}
	return (nb);
}

t_sprite		*zeroing_sprite(t_sprite *sprites)
{
	sprites->sprite_x = NULL;
	sprites->sprite_y = NULL;
	return (sprites);
}

t_sprite		*catch_sprite(t_spec *inf, int i)
{
	int			nb;
	int			j;
	t_sprite	*sprites;

	inf->sprite_nb = get_sprite_number(inf->map);
	nb = inf->sprite_nb;
	if (!(sprites = (t_sprite*)malloc(sizeof(t_sprite))))
		return (NULL);
	sprites = zeroing_sprite(sprites);
	if (!(sprites->sprite_x = (double*)malloc(sizeof(double) * inf->sprite_nb)))
		return (NULL);
	if (!(sprites->sprite_y = (double*)malloc(sizeof(double) * inf->sprite_nb)))
		return (NULL);
	while (inf->map[++i])
	{
		j = -1;
		while (inf->map[i][++j])
			if (inf->map[i][j] == '2')
			{
				nb -= 1;
				sprites->sprite_y[nb] = i + 0.5;
				sprites->sprite_x[nb] = j + 0.5;
			}
	}
	return (sprites);
}

void			sprite_math(t_spec *inf, int i)
{
	inf->sprite_x = inf->sprites->sprite_x[i] - inf->pos_x;
	inf->sprite_y = inf->sprites->sprite_y[i] - inf->pos_y;
	inf->inv_det = 1.0 / (inf->plane_x * inf->dir_y -
		inf->dir_x * inf->plane_y);
	inf->trans_x = inf->inv_det * (inf->dir_y * inf->sprite_x -
			inf->dir_x * inf->sprite_y);
	inf->trans_y = inf->inv_det * (-inf->plane_y * inf->sprite_x +
			inf->plane_x * inf->sprite_y);
	inf->sprite_screen_x = (int)((inf->res_x / 2) * (1 + inf->trans_x /
				inf->trans_y));
	inf->sprite_height = abs((int)(inf->res_y / (inf->trans_y)));
	inf->draw_start_y = -inf->sprite_height / 2 + inf->res_y / 2;
	if (inf->draw_start_y < 0)
		inf->draw_start_y = 0;
	inf->draw_end_y = inf->sprite_height / 2 + inf->res_y / 2;
	if (inf->draw_end_y >= inf->res_y)
		inf->draw_end_y = inf->res_y - 1;
	inf->sprite_width = abs((int)(inf->res_y / (inf->trans_y)));
	inf->draw_start_x = -inf->sprite_width / 2 + inf->sprite_screen_x;
	if (inf->draw_start_x < 0)
		inf->draw_start_x = 0;
	inf->draw_end_x = inf->sprite_width / 2 + inf->sprite_screen_x;
	if (inf->draw_end_x >= inf->res_x)
		inf->draw_end_x = inf->res_x - 1;
}

void			sprite_set(t_spec *inf, double *z_buffer)
{
	int i;

	i = 0;
	while (i < inf->sprite_nb)
	{
		sprite_math(inf, i);
		inf->stripe = inf->draw_start_x;
		while (inf->stripe < inf->draw_end_x)
		{
			inf->tex_x = (int)(256 * (inf->stripe - (-inf->sprite_width / 2 +
							inf->sprite_screen_x)) * inf->text->twidth[4] /
					inf->sprite_width) / 256;
			if (inf->trans_y > 0 && inf->stripe > 0 && inf->stripe <
					inf->res_x && inf->trans_y < z_buffer[inf->stripe])
				sprite_drawing(inf);
			inf->stripe++;
		}
		i++;
	}
}
