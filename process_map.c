/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:13:52 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/06 18:13:53 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_spec		*set_dir(t_spec *inf, double dir_x, double dir_y)
{
	inf->dir_x = dir_x;
	inf->dir_y = dir_y;
	return (inf);
}

t_spec		*set_plane(t_spec *inf, double plane_x, double plane_y)
{
	inf->plane_x = plane_x;
	inf->plane_y = plane_y;
	return (inf);
}

t_spec		*set_player(t_spec *inf)
{
	inf = get_letter(inf);
	if (inf->orien == 'N')
	{
		inf = set_dir(inf, 0, -1);
		inf = set_plane(inf, 0.66, 0);
	}
	if (inf->orien == 'S')
	{
		inf = set_dir(inf, 0, 1);
		inf = set_plane(inf, -0.66, 0);
	}
	if (inf->orien == 'E')
	{
		inf = set_dir(inf, 1, 0);
		inf = set_plane(inf, 0, 0.66);
	}
	if (inf->orien == 'W')
	{
		inf = set_dir(inf, -1, 0);
		inf = set_plane(inf, 0, -0.66);
	}
	if (valid_map(inf->map) == -1)
		return (free_all_spec(inf, "use an invalid map"));
	return (inf);
}
