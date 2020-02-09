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
		moveSpeed + (inf->dir_y < 0 ? -0.20 : 0.20))] != '1')
		inf->pos_x += inf->dir_y * moveSpeed;
	if (inf->map[(int)(inf->pos_y + inf->dir_y * moveSpeed + (-inf->dir_x <
		0 ? -0.20 : 0.20))][(int)inf->pos_x] != '1')
		inf->pos_y += -inf->dir_x * moveSpeed;
	inf->up->key_a = 0;
}

void		move_right(t_spec *inf)
{
	if (inf->map[(int)(inf->pos_y)][(int)(inf->pos_x + -inf->dir_y * moveSpeed +
		(-inf->dir_y < 0 ? -0.20 : 0.20))] != '1')
		inf->pos_x += -inf->dir_y * moveSpeed;
	if (inf->map[(int)(inf->pos_y + inf->dir_y * moveSpeed + (inf->dir_x < 0 ?
		-0.20 : 0.20))][(int)inf->pos_x] != '1')
		inf->pos_y += inf->dir_x * moveSpeed;
	inf->up->key_d = 0;
}

void		move_forward(t_spec *inf)
{
	if (inf->map[(int)(inf->pos_y)][(int)(inf->pos_x + inf->dir_x *
		moveSpeed + (inf->dir_x < 0 ? -0.20 : 0.20))] != '1')
		inf->pos_x += inf->dir_x * moveSpeed;
	if (inf->map[(int)(inf->pos_y + inf->dir_y * moveSpeed + (inf->dir_y < 0 ?
		-0.20 : 0.20))][(int)inf->pos_x] != '1')
		inf->pos_y += inf->dir_y * moveSpeed;
	inf->up->key_w = 0;
}

void		move_backward(t_spec *inf)
{
	if (inf->map[(int)(inf->pos_y)][(int)(inf->pos_x -
		inf->dir_x * moveSpeed + (-inf->dir_x < 0 ?
		-0.20 : 0.20))] != '1')
		inf->pos_x -= inf->dir_x * moveSpeed;
	if (inf->map[(int)(inf->pos_y - inf->dir_y *
		moveSpeed + (-inf->dir_y < 0 ?
		-0.20 : 0.20))][(int)inf->pos_x] != '1')
		inf->pos_y -= inf->dir_y * moveSpeed;
	inf->up->key_s = 0;
}
