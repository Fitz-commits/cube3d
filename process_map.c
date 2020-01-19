#include "cube3d.h"

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

t_spec		*set_oxy(t_spec *inf, char o, int y, int x)
{
	inf->posX = x + 0.5;
	inf->posY = y + 0.5;
	inf->orien = o;
	return (inf);
}
t_spec		*get_letter(t_spec *inf)
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
	return (NULL);
}
t_spec		*set_dir(t_spec *inf, double dirX, double dirY)
{
	inf->dirX = dirX;
	inf->dirY = dirY;
	return (inf);
}
t_spec		*set_plane(t_spec *inf, double planeX, double planeY)
{
	inf->planeX = planeX;
	inf->planeY = planeY;
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
		inf = set_plane(inf, 0.66, 0);
	}
	if (inf->orien == 'E')
	{
		inf = set_dir(inf, 1, 0);
		inf = set_plane(inf, 0, 0.66);
	}
	if (inf->orien == 'W')
	{
		inf = set_dir(inf, -1, 0);
		inf = set_plane(inf, 0, 0.66);
	}
	if (valid_map(inf->map) == -1)
		return (free_all_spec(inf));
	return (inf);
}