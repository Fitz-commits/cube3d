/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:49:31 by cdelaby           #+#    #+#             */
/*   Updated: 2019/12/16 15:49:32 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>

char            *addbackn(char *line)
{
    char *buffer;
    char *cpy;
    char *cpy_buf;

    if (!(buffer = (char*)(malloc(ft_strlen(line) + 2))))
        return (free_line_char(line));
    cpy_buf = buffer;
    cpy = line;
    while (*line)
        *buffer++ = *line++;
    *buffer++ = '\n';
    *buffer = '\0';
    free(cpy);
    return (cpy_buf);
}

char		**delete_space(char **map)
{
	int i;
	int j;
	char *temp;
	char *tempcp;
	int space;

	i = 0;
	while(map[i])
	{
		space = 0;
		j = 0;
		while(map[i][j])
			if(map[i][j++] == ' ')
				space += 1;
		if (!(temp = (char*)malloc(ft_strlen(map[i]) - space + 1)))
				return (NULL);
			tempcp = temp;
			j = 0;
			while (map[i][j++])
				if (map[i][j-1] != ' ')
					*tempcp++ = map[i][j-1]; //might want null termination
            *tempcp = '\0';
			free(map[i]);
			map[i++] = temp;	
	}
	return (map);
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

t_spec      *zero_spec(t_spec *specs)
{
    if (!(specs = (t_spec*)malloc(sizeof(t_spec))))
        return (NULL);
	specs->pathNO = NULL;
	specs->pathSO = NULL;
    specs->pathEA = NULL;
    specs->pathWE = NULL;
    specs->pathS = NULL;
    specs->map = NULL;
    return(specs);
}
t_spec      *spec_hand_bis(t_spec *specs, char **spl_l)
{
    if (!(ft_strncmp(spl_l[0], "F", 1)))
        specs->colorF = ft_ar_to_int(spl_l[1]);
    if (!(ft_strncmp(spl_l[0], "C", 1)))
        specs->colorC = ft_ar_to_int(spl_l[1]);
    if (!(ft_strncmp(spl_l[0], "R", 1)))
    {
        specs->res_x = ft_atoi(spl_l[1]);
        specs->res_y = ft_atoi(spl_l[2]);
    }
    free_map(spl_l);
    return (specs);
}

t_spec		*map_builder(t_spec *specs, char *line, int fd)
{
	char *buffer;
    int ret;
    
    buffer = addbackn(line);
    while ((ret = get_next_line(fd, &line) == 1))
    {
        if (!(buffer = ft_strnaddmod(buffer, line)))
            return(free_line(line));
        free(line);
    }
    free(line); // Might not work
    if(!(specs->map = ft_split(buffer, '\n')))
        return (free_spec(specs));
    free_line(buffer);
    return(specs);
}

t_spec      *specHandling(t_spec *specs, char *line)
{
    char **spl_l;

    if (line[0] == '\0')
        return (specs);
    if (!(spl_l = ft_split(line, ' ')))
        return (free_spec(specs));
    if ((!(ft_strncmp(spl_l[0], "NO", 2))))
        if (!(specs->pathNO = ft_strdup(spl_l[1])))
            return (free_sp_spl(specs, spl_l));
    if (!(ft_strncmp(spl_l[0], "SO", 2)))
        if (!(specs->pathSO = ft_strdup(spl_l[1])))
            return (free_sp_spl(specs, spl_l));
    if (!(ft_strncmp(spl_l[0], "WE", 2)))
        if (!(specs->pathWE = ft_strdup(spl_l[1])))
            return (free_sp_spl(specs, spl_l));
    if (!(ft_strncmp(spl_l[0], "EA", 2)))
        if (!(specs->pathEA = ft_strdup(spl_l[1])))
            return (free_sp_spl(specs, spl_l));
    if (!(ft_strncmp(spl_l[0], "S", 1)) && spl_l[0][1] == 0)
        if (!(specs->pathS = ft_strdup(spl_l[1])))
            return (free_sp_spl(specs, spl_l));
    return (spec_hand_bis(specs, spl_l));
}

t_spec      *initSpec(char *pathToCub)
{
    int fd;
    int ret;
    char *line;
    t_spec *specs;

    if (!(specs = (t_spec*)malloc(sizeof(t_spec))))
        return (NULL);
    if(!(fd = (open(pathToCub, O_RDONLY))))
        return (free_spec(specs));
    while((ret = get_next_line(fd, &line) == 1) && (line[0] != '1'))
    {
        if(!(specs = specHandling(specs, line)))
            return (free_line(line));
        free(line);
    }
    if(!(specs = map_builder(specs, line, fd)))
        return (free_line(line)); //need to free the whole struc in case of error
	if (!(specs->map = delete_space(specs->map)))
		return (free_all_spec(specs));
    specs->sprites = catchSprite(specs);
    return (set_player(specs));
}
/*
int     main()
{
    t_spec *specs;
    specs = initSpec("./map.cub");
    int i = 0;
    printf("%d %d\n", specs->resX, specs->resY);
    printf("%s\n", specs->pathNO);
    printf("%s\n", specs->pathSO);
    printf("%s\n", specs->pathWE);
    printf("%s\n", specs->pathEA);
    printf("%s\n", specs->pathS);
    printf("%X %X\n", specs->colorC, specs->colorF);
    while(specs->map[i])
        printf("%s\n", specs->map[i++]);
    printf("%d", valid_map(specs->map));
    free_all_spec(specs);
}
*/