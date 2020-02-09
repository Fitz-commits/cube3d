/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:00:12 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 19:25:54 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int				key_update(t_spec *inf)
{
	if (inf->up->key_a)
		move_left(inf);
	if (inf->up->key_d)
		move_right(inf);
	if (inf->up->key_w)
		move_forward(inf);
	if (inf->up->key_s)
		move_backward(inf);
	if (inf->up->key_left)
		rotate_left(inf);
	if (inf->up->key_right)
		rotate_right(inf);
	if (inf->up->key_exit)
		exit(0);
	return (1);
}

int				key_hook(int key, void *param)
{
	t_spec *inf;

	inf = (t_spec*)param;
	if (key == K_W)
		return (inf->up->key_w = 1);
	if (key == K_D)
		return (inf->up->key_d = 1);
	if (key == K_A)
		return (inf->up->key_a = 1);
	if (key == K_S)
		return (inf->up->key_s = 1);
	if (key == K_LEFT)
		return (inf->up->key_left = 1);
	if (key == K_RIGHT)
		return (inf->up->key_right = 1);
	if (key == K_ESC)
		free_all_spect(inf, NULL);
	if (key == 17)
		free_all_spect(inf, NULL);
	return (0);
}

int				ft_close(t_spec *inf)
{
	free_all_spect(inf, NULL);
	return (0);
}

t_spec			*zero_up(t_spec *specs)
{
	t_up		updates;

	specs->up = &updates;
	specs->up->key_a = 0;
	specs->up->key_w = 0;
	specs->up->key_s = 0;
	specs->up->key_d = 0;
	specs->up->key_right = 0;
	specs->up->key_left = 0;
	specs->up->key_exit = 0;
	return (specs);
}
