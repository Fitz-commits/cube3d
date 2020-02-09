/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:47:22 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 19:28:21 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void			set_img(t_spec *inf)
{
	int j;
	int k;
	int l;

	inf->imgptr = mlx_new_image(inf->mlx, inf->res_x, inf->res_y);
	inf->charimgptr = mlx_get_data_addr(inf->imgptr, &j, &k, &l);
	inf->intimgptr = (int*)inf->charimgptr;
}

t_spec			*init_cube(t_spec *inf)
{
	inf->mlx = mlx_init();
	inf->win_ptr = mlx_new_window(inf->mlx, inf->res_x, inf->res_y, "cube3d");
	if (!(inf->text = init_void(inf)))
		free_all_spect(inf, "couldn't init void textures");
	set_img(inf);
	return (inf);
}

t_spec			*init_spec(char *path_to_cub)
{
	int			fd;
	int			ret;
	char		*line;
	t_spec		*specs;

	if (!(specs = (t_spec*)malloc(sizeof(t_spec))))
		return (NULL);
	if (!(fd = (open(path_to_cub, O_RDONLY))))
		return (free_spec(specs));
	while ((ret = get_next_line(fd, &line) == 1) && (line[0] != '1'))
	{
		if (!(specs = spec_handling(specs, line)))
			return (free_line(line));
		free(line);
	}
	if (!(specs = map_builder(specs, line, fd)))
		return (free_all_spec(specs, "build map"));
	if (!(specs->map = delete_space(specs->map, 0)))
		return (free_all_spec(specs, "delete spaces"));
	if (!(specs->sprites = catch_sprite(specs, 0)))
		return (free_all_spec(specs, "init the sprites"));
	specs = zero_up(specs);
	return (set_player(specs));
}

int				main(int ac, char **av)
{
	t_spec *inf;

	if (ac == 1 || ac > 3)
		return (pr_err("load the map"));
	if (!(inf = init_spec(av[1])))
		exit(0);
	inf = init_cube(inf);
	if (ac == 3 && !(ft_strcmp(av[2], "--save")))
		inf->save = 1;
	mlx_hook(inf->win_ptr, 2, 0, key_hook, inf);
	mlx_hook(inf->win_ptr, 3, 0, key_hook, inf);
	mlx_hook(inf->win_ptr, 17, 0, ft_close, inf);
	mlx_loop_hook(inf->mlx, draw, inf);
	mlx_loop(inf->mlx);
}
