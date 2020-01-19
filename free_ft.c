#include "cube3d.h"

t_spec		*free_spec(t_spec *specs)
{
    free(specs);
    return (NULL);
}

t_spec		*free_line(char *line)
{
    free(line);
    return (NULL);
}

char		*free_line_char(char *line)
{
    free(line);
    return (NULL);
}

t_spec		*free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	return (NULL);

}

t_spec		*free_all_spec(t_spec *specs)
{
    if (specs->pathNO)
        free(specs->pathNO);
    if (specs->pathSO)
        free(specs->pathSO);
    if (specs->pathEA)
        free(specs->pathEA);
    if (specs->pathWE)
        free(specs->pathWE);
    if (specs->pathS)
        free(specs->pathS);
    if (specs->map)
		free_map(specs->map);
	return (free_spec(specs));
}

t_spec		*free_sp_spl(t_spec *specs, char **spl_l)
{
	free_map(spl_l);
	return (free_all_spec(specs));
}