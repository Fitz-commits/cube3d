#include "cube3d.h"

t_spec		*set_pos(t_spec *specs, int x, int y, char dir)
{
	specs->posX = x;
	specs->posX = y;
	specs->orien = dir;
	return (specs);
}

t_spec		*prep_pos(t_spec *specs)
{
	int i;
	int j;

	i = 0;
	while (specs->map[i])
	{
		j = 0;
		while (specs->map[i][j])
		{
			if (specs->map[i][j] == 'N')
				return (set_pos(specs, j, i, 'N'));
			if (specs->map[i][j] == 'S')
				return (set_pos(specs, j, i, 'S'));
			if (specs->map[i][j] == 'E')
				return (set_pos(specs, j, i, 'E'));
			if (specs->map[i][j] == 'W')
				return (set_pos(specs, j, i, 'W'));
			j++;
		}
		i++;
	}
	return (free_all_spec(specs));
}

int		valid_map(char **map)
{
	int i;
	int j;
	int sizey;
	
	j = 0;
	while(map[0][j])
		if (map[0][j++] != '1')
			return (-1);
	i = 0;
	while (map[i] && map[i][j - 1])
		if (map[i++][j-1] != '1')
			return (-1);
	j = 0;
	while(map[i - 1] && map[i - 1][j])
		if (map[i - 1][j++] != '1')
			return (-1);
	i = 0;
	while (map[i] && map[i][0])
		if (map[i++][0] != '1')
			return (-1);
	return (1);
}
