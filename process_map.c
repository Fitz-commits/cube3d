#include "cube3d.h"

int		valid_map(char **map)
{
	int i;
	int j;
	
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
	inf->pos_x = x + 0.5;
	inf->pos_y = y + 0.5;
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

t_spec		*set_dir(t_spec *inf, double dir_x, double dir_y)
{
	inf->dir_x = dir_x;
	inf->dir_y= dir_y;
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
int			get_sprite_number(char **map)
{
	int i;
	int j;
	int nb;

	i = 0;
	i = -1;
	j = -1;
	nb = 0;
	while (map[++i])
		{
			j = -1;
			while (map[i][++j])
				if (map[i][j] == '2')
					nb++;
		}
	return (nb);
}

t_sprite	*zeroingSprite(t_sprite *sprites)
{
	sprites->sprite_x = NULL;
	sprites->sprite_y = NULL;
	return (sprites);
}

t_sprite	*catchSprite(t_spec *inf)
{
	int i;
	int nb;
	int j;
	t_sprite *sprites;

	i = 0;
	inf->sprite_nb = get_sprite_number(inf->map);
	nb = inf->sprite_nb;
	if (!(sprites = (t_sprite*)malloc(sizeof(t_sprite))))
		return (NULL);
	sprites = zeroingSprite(sprites);
	if (!(sprites->sprite_x = (double*)malloc(sizeof(double) * inf->sprite_nb)))
		return (NULL); // need to implement a free
	if (!(sprites->sprite_y = (double*)malloc(sizeof(double) * inf->sprite_nb)))
		return (NULL); // need to implement a free
	while (inf->map[++i])
	{
		j = -1;
		while (inf->map[i][++j])
			if (inf->map[i][j] == '2')
				{
					nb -= 1;
					sprites->sprite_x[nb] = i + 0.5;
					sprites->sprite_y[nb] = j + 0.5; 
				}
	}
	return (sprites);
}
double		*cacl_dist(t_spec *inf)
{
	double		*dist;
	int i;

	i = -1;
	if (!(dist = (double*)malloc(sizeof(double) * inf->sprite_nb)))
		return (NULL);// free implementation
	while (++i < inf->sprite_nb)
		dist[i] = (inf->pos_x - inf->sprites->sprite_x[i]) * (inf->pos_x - inf->sprites->sprite_x[i])
			+ (inf->pos_y - inf->sprites->sprite_y[i]) * (inf->pos_y - inf->sprites->sprite_y[i]);
	return (dist);
}

void	swap_sprite(t_spec *inf, int i, int j)
{
	double temp_x;
	double temp_y;

	temp_x = inf->sprites->sprite_x[i];
	temp_y = inf->sprites->sprite_y[i];
	inf->sprites->sprite_x[i] = inf->sprites->sprite_x[j];
	inf->sprites->sprite_y[i] = inf->sprites->sprite_y[j];
	inf->sprites->sprite_x[j] = temp_x;
	inf->sprites->sprite_y[j] = temp_y;
}

t_sprite	*buble_sort_sprite(t_spec *inf)
{
	int i;
	int j;
	double tempdist;
	double *dist;

	i = -1;
	j = -1;
	dist = cacl_dist(inf);
	while (++i < inf->sprite_nb - 1)
		while (++j < inf->sprite_nb - i - 1)
			if (dist[j] < dist[j + 1])
			{
				swap_sprite(inf, j,j + 1);
				tempdist = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = dist[j];
			}
	free(dist);
	return (inf->sprites);
}