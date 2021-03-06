/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texHandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:19:05 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/19 17:19:11 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_spec		*check_data(t_spec *inf)
{
	if (!(inf->map))
		return (free_all_spec(inf, "find the map"));
	if (!(inf->path_no))
		return (free_all_spec(inf, "find the path_no"));
	if (!(inf->path_so))
		return (free_all_spec(inf, "find the path_so"));
	if (!(inf->path_s))
		return (free_all_spec(inf, "find the path_s"));
	if (!(inf->path_ea))
		return (free_all_spec(inf, "find the path_ea"));
	if (!(inf->path_we))
		return (free_all_spec(inf, "find the path_we"));
	return (NULL);
}

t_text		*zeroing(t_text *text)
{
	text->chartext = NULL;
	text->itext = NULL;
	text->vtext = NULL;
	return (text);
}

t_text		*init_void(t_spec *inf)
{
	if (!(inf->text = malloc(sizeof(t_text))))
		return (free_all_spect(inf, "alloc text"));
	inf->text = zeroing(inf->text);
	if (!(inf->text->vtext = (void**)malloc(sizeof(void*) * 5)))
		return (free_all_spect(inf, "alloc vtext"));
	if (!(inf->text->vtext[0] = mlx_xpm_file_to_image(inf->mlx, inf->path_ea,
		&inf->text->twidth[0], &inf->text->theight[0])))
		return (free_all_spect(inf, "allocate path_ea"));
	if (!(inf->text->vtext[1] = mlx_xpm_file_to_image(inf->mlx, inf->path_we,
		&inf->text->twidth[1], &inf->text->theight[1])))
		return (free_all_spect(inf, "alloc path_we"));
	if (!(inf->text->vtext[2] = mlx_xpm_file_to_image(inf->mlx, inf->path_no,
		&inf->text->twidth[2], &inf->text->theight[2])))
		return (free_all_spect(inf, "alloc path_no"));
	if (!(inf->text->vtext[3] = mlx_xpm_file_to_image(inf->mlx, inf->path_so,
		&inf->text->twidth[3], &inf->text->theight[3])))
		return (free_all_spect(inf, "alloc path_so"));
	if (!(inf->text->vtext[4] = mlx_xpm_file_to_image(inf->mlx, inf->path_s,
		&inf->text->twidth[4], &inf->text->theight[4])))
		return (free_all_spect(inf, "alloc path_s"));
	if (!(inf->text = get_adress(inf->text)))
		return (free_all_spect(inf, "get address"));
	return (inf->text);
}

void		set_texture(t_spec *inf)
{
	inf->tex_x = (int)(inf->wall_x * (double)(inf->text->twidth[0]));
	if (inf->side == 0 && inf->ray_dir_x > 0)
		inf->tex_x = inf->text->twidth[0] - inf->tex_x - 1;
	if (inf->side == 1 && inf->ray_dir_y < 0)
		inf->tex_x = inf->text->twidth[0] - inf->tex_x - 1;
	inf->step = 1.0 * inf->text->theight[0] / inf->line_height;
	inf->tex_pos = (inf->draw_start - inf->res_y / 2 +
			inf->line_height / 2) * inf->step;
}

t_text		*get_adress(t_text *text)
{
	int i;

	i = 0;
	if (!(text->chartext = (char**)malloc(sizeof(char*) * 5)))
		return (NULL);
	while (i < 5)
	{
		text->chartext[i] = mlx_get_data_addr(text->vtext[i], &text->tsl[i],
			&text->bpp[i], &text->med[i]);
		i++;
	}
	i = -1;
	if (!(text->itext = (int**)malloc(sizeof(int*) * 5)))
		return (NULL);
	while (++i < 5)
		text->itext[i] = (int*)text->chartext[i];
	return (text);
}
