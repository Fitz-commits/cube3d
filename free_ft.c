#include "cube3d.h"

int     free_spec( t_spec *specs)
{
    free(specs);
    return (0);
}

int		free_map(char **map)
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
	return (0);

}

int     free_all_spec(t_spec *specs)
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
	return(free_spec(specs));
}