/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:02:43 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 19:51:57 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int				valid_map(char **map)
{
	int i;
	int j;

	j = 0;
	while (map[0][j])
		if (map[0][j++] != '1')
			return (-1);
	i = 0;
	while (map[i] && map[i][j - 1])
		if (map[i++][j - 1] != '1')
			return (-1);
	j = 0;
	while (map[i - 1] && map[i - 1][j])
		if (map[i - 1][j++] != '1')
			return (-1);
	i = 0;
	while (map[i] && map[i][0])
		if (map[i++][0] != '1')
			return (-1);
	return (1);
}

t_spec			*set_oxy(t_spec *inf, char o, int y, int x)
{
	inf->pos_x = x + 0.5;
	inf->pos_y = y + 0.5;
	inf->orien = o;
	return (inf);
}

t_spec			*get_letter(t_spec *inf)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (inf->map[j])
	{
		i = 0;
		while (inf->map[j][i])
		{
			if (inf->map[j][i] == 'N')
				return (set_oxy(inf, 'N', j, i));
			if (inf->map[j][i] == 'S')
				return (set_oxy(inf, 'S', j, i));
			if (inf->map[j][i] == 'W')
				return (set_oxy(inf, 'W', j, i));
			if (inf->map[j][i] == 'E')
				return (set_oxy(inf, 'E', j, i));
			i++;
		}
		j++;
	}
	return (free_all_spec(inf, "find orientation specifier"));
}

t_spec			*zero_spec(t_spec *specs)
{
	specs->path_no = NULL;
	specs->path_so = NULL;
	specs->path_ea = NULL;
	specs->path_we = NULL;
	specs->path_s = NULL;
	specs->map = NULL;
	specs->mlx = NULL;
	specs->win_ptr = NULL;
	specs->imgptr = NULL;
	specs->charimgptr = NULL;
	specs->intimgptr = NULL;
	specs->text = NULL;
	specs->sprites = NULL;
	specs->save = 0;
	specs->orien = 0;
	return (specs);
}

char			*ft_strnaddmod(char *rest, char *s2)
{
	char			*copy;
	char			*copy_cpp;
	char			*rest_cpp;

	if (rest == NULL)
		return (ft_strdup(s2));
	copy = ft_strdup(rest);
	free(rest);
	copy_cpp = copy;
	if (!(rest = (char*)malloc(sizeof(char) * (ft_strlen(copy)
						+ ft_strlen(s2) + 2))))
		return (0);
	rest_cpp = rest;
	while (*copy)
		*rest++ = *copy++;
	while (*s2)
		*rest++ = *s2++;
	free(copy_cpp);
	*rest++ = '\n';
	*rest = 0;
	return (rest_cpp);
}
