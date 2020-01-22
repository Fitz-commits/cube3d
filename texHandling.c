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
#include <stdio.h>
#include "cube3d.h"
t_text	*free_text(t_spec *inf)
{
	int i;
	i = 0;
	while (i < 5)
		if(inf->text->vtext[i++])
			mlx_destroy_image(inf->mlx, inf->text->vtext[i - 1]);
	return (inf->text);
}
t_text	*zeroing(t_text *text)
{
	int i;

	i = 0;
	while (i < 5)
		text->vtext[i++] = NULL;
	return (text);
}
t_text	*init_void(t_spec *inf)
{
	int l;
	int i;

	if (!(inf->text = malloc(sizeof(t_text))))
		return (NULL);
	if(!(inf->text->vtext = (void**)malloc(sizeof(void*) * 5)))
		return (NULL);
	inf->text = zeroing(inf->text);
	if (!(inf->text->vtext[0] = mlx_xpm_file_to_image(inf->mlx, inf->pathNO, 
		&inf->text->twidth[0], &inf->text->theight[0])))
		return (free_text(inf));
	if (!(inf->text->vtext[1] = mlx_xpm_file_to_image(inf->mlx, inf->pathEA, 
		&inf->text->twidth[1], &inf->text->theight[1])))
			return (free_text(inf));
	if (!(inf->text->vtext[2] = mlx_xpm_file_to_image(inf->mlx, inf->pathSO, 
		&inf->text->twidth[2], &inf->text->theight[2])))
			return (free_text(inf));
	if (!(inf->text->vtext[3] = mlx_xpm_file_to_image(inf->mlx, inf->pathWE, 
		&inf->text->twidth[3], &inf->text->theight[3])))
			return (free_text(inf));
	if (!(inf->text->vtext[4] = mlx_xpm_file_to_image(inf->mlx, inf->pathS, 
		&inf->text->twidth[4], &inf->text->theight[4])))
			return (free_text(inf));
	inf->text = get_adress(inf->text);
	return (inf->text);
}

t_text	*get_adress(t_text *text)
{
	int i;

	i = 0;
	if(!(text->chartext = (char**)malloc(sizeof(char*) * 5)))
		return (NULL);
	while (i < 5)
	{
		text->chartext[i] = mlx_get_data_addr(text->vtext[i], &text->tsl[i],
			&text->bpp[i], &text->med[i]);
		i++;
	}
	i = -1;
	if(!(text->itext = (int**)malloc(sizeof(int*) * 5)))
		return (NULL);
	while (++i < 5)
		text->itext[i] = (int*)text->chartext[i];
	return (text);
}
