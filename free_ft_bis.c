/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:44:44 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/06 15:46:58 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void			free_sprites(t_sprite *sprites)
{
	if (sprites->sprite_x)
		free(sprites->sprite_x);
	if (sprites->sprite_y)
		free(sprites->sprite_y);
	free(sprites);
}

t_text			*free_text(t_spec *inf)
{
	if (inf->text->vtext)
	{
		free(inf->text->vtext);
	}
	if (inf->text->chartext)
		free(inf->text->chartext);
	if (inf->text->itext)
		free(inf->text->itext);
	free(inf->text);
	return (NULL);
}

t_spec			*free_all_spec(t_spec *specs, char *error)
{
	if (specs->path_no)
		free(specs->path_no);
	if (specs->path_so)
		free(specs->path_so);
	if (specs->path_ea)
		free(specs->path_ea);
	if (specs->path_we)
		free(specs->path_we);
	if (specs->path_s)
		free(specs->path_s);
	if (specs->text)
		free_text(specs);
	if (specs->sprites)
		free_sprites(specs->sprites);
	if (specs->mlx)
		mlx_destroy_window(specs->mlx, specs->win_ptr);
	if (specs->map)
		free_map(specs->map);
	pr_err(error);
	return (free_spec(specs));
}

t_text			*free_all_spect(t_spec *specs, char *error)
{
	if (specs->path_no)
		free(specs->path_no);
	if (specs->path_so)
		free(specs->path_so);
	if (specs->path_ea)
		free(specs->path_ea);
	if (specs->path_we)
		free(specs->path_we);
	if (specs->path_s)
		free(specs->path_s);
	if (specs->text)
		free_text(specs);
	if (specs->sprites)
		free_sprites(specs->sprites);
	if (specs->mlx)
		mlx_destroy_window(specs->mlx, specs->win_ptr);
	if (specs->map)
		free_map(specs->map);
	pr_err(error);
	return (free_spect(specs));
}

t_spec			*free_sp_spl(t_spec *specs, char **spl_l, char *error)
{
	free_map(spl_l);
	return (free_all_spec(specs, error));
}
