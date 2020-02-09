/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:56:33 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 17:56:34 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void			draw_inside(t_spec *inf, int draw_start, int draw_end,
	int tex_num)
{
	int y;
	int tex_y;
	int color;

	y = 0;
	while (y <= draw_start)
		inf->intimgptr[(y++ * inf->res_x) + inf->x] = inf->color_c;
	while (y < draw_end)
	{
		tex_y = (int)inf->texPos & (inf->text->theight[tex_num] - 1);
		inf->texPos += inf->step;
		color = inf->text->itext[tex_num][inf->text->theight[tex_num] *
			tex_y + inf->texX];
		inf->intimgptr[(y++ * inf->res_x) + inf->x] = color;
	}
	while (y < inf->res_y)
		inf->intimgptr[(y++ * inf->res_x) + inf->x] = inf->color_f;
}

void			sprite_drawing(t_spec *inf)
{
	inf->y = inf->draw_start_y;
	while (inf->y < inf->draw_end_y)
	{
		inf->d = (inf->y) * 256 - inf->res_y * 128 + inf->sprite_height * 128;
		inf->tex_y = ((inf->d * inf->text->theight[4]) /
				inf->sprite_height) / 256;
		inf->s_color = inf->text->itext[4][inf->text->twidth[4]
			* inf->tex_y + inf->tex_x];
		if ((inf->s_color & 0x00FFFFFF) != 0)
			inf->intimgptr[(inf->y * inf->res_x) + inf->stripe] = inf->s_color;
		inf->y++;
	}
}

int				draw(t_spec *inf)
{
	double z_buffer[inf->res_x];

	key_update(inf);
	inf->x = 0;
	while (inf->x < inf->res_x)
		put_pixel_img(inf, z_buffer);
	if (!(inf->sprites = buble_sort_sprite(inf)))
		free_all_spec(inf, "sort sprites");
	sprite_set(inf, z_buffer);
	if (!inf->save)
		mlx_put_image_to_window(inf->mlx, inf->win_ptr, inf->imgptr, 0, 0);
	else
	{
		save_bmp(inf);
		free_all_spect(inf, NULL);
	}
	return (1);
}
