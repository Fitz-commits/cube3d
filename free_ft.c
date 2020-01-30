#include "cube3d.h"

t_spec		*free_spec(t_spec *specs)
{
    free(specs);
    exit(0);
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

void        free_sprites(t_sprite *sprites)
{
    if (sprites->sprite_x)
        free(sprites->sprite_x);
    if (sprites->sprite_y)
        free(sprites->sprite_y);
    free(sprites);
}

t_text	*free_text(t_spec *inf)
{
	int i;
	i = 0;
    if (inf->text->vtext)
    {
	    while (i < 5)
		    if(inf->text->vtext[i++])
			    mlx_destroy_image(inf->mlx, inf->text->vtext[i - 1]);
        free(inf->text->vtext);
    }
    if (inf->text->chartext)
        free(inf->text->chartext);
    if (inf->text->itext)
        free(inf->text->itext);
    free(inf->text);
	return (inf->text);
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
    if (specs->mlx)
        mlx_destroy_window(specs->mlx, specs->win_ptr);
    if (specs->text)
        free_text(specs->text);
    if (specs->sprites)
        free_sprites(specs->sprites);
    if (specs->map)
		free_map(specs->map);
	return (free_spec(specs));
}

t_spec		*free_sp_spl(t_spec *specs, char **spl_l)
{
	free_map(spl_l);
	return (free_all_spec(specs));
}
