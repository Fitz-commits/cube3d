/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:59:25 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 17:59:26 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		move_left(t_spec *inf)
{
	if (inf->map[(int)(inf->pos_y)][(int)(inf->pos_x + inf->dir_y *
		MOVESPEED + (inf->dir_y < 0 ? -0.20 : 0.20))] != '1')
		inf->pos_x += inf->dir_y * MOVESPEED;
	if (inf->map[(int)(inf->pos_y + inf->dir_y * MOVESPEED + (-inf->dir_x <
		0 ? -0.20 : 0.20))][(int)inf->pos_x] != '1')
		inf->pos_y += -inf->dir_x * MOVESPEED;
	inf->up->key_a = 0;
}

void		move_right(t_spec *inf)
{
	if (inf->map[(int)(inf->pos_y)][(int)(inf->pos_x + -inf->dir_y * MOVESPEED +
		(-inf->dir_y < 0 ? -0.20 : 0.20))] != '1')
		inf->pos_x += -inf->dir_y * MOVESPEED;
	if (inf->map[(int)(inf->pos_y + inf->dir_y * MOVESPEED + (inf->dir_x < 0 ?
		-0.20 : 0.20))][(int)inf->pos_x] != '1')
		inf->pos_y += inf->dir_x * MOVESPEED;
	inf->up->key_d = 0;
}

void		move_forward(t_spec *inf)
{
	if (inf->map[(int)(inf->pos_y)][(int)(inf->pos_x + inf->dir_x *
		MOVESPEED + (inf->dir_x < 0 ? -0.20 : 0.20))] != '1')
		inf->pos_x += inf->dir_x * MOVESPEED;
	if (inf->map[(int)(inf->pos_y + inf->dir_y * MOVESPEED + (inf->dir_y < 0 ?
		-0.20 : 0.20))][(int)inf->pos_x] != '1')
		inf->pos_y += inf->dir_y * MOVESPEED;
	inf->up->key_w = 0;
}

void		move_backward(t_spec *inf)
{
	if (inf->map[(int)(inf->pos_y)][(int)(inf->pos_x -
		inf->dir_x * MOVESPEED + (-inf->dir_x < 0 ?
		-0.20 : 0.20))] != '1')
		inf->pos_x -= inf->dir_x * MOVESPEED;
	if (inf->map[(int)(inf->pos_y - inf->dir_y *
		MOVESPEED + (-inf->dir_y < 0 ?
		-0.20 : 0.20))][(int)inf->pos_x] != '1')
		inf->pos_y -= inf->dir_y * MOVESPEED;
	inf->up->key_s = 0;
}
