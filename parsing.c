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
}
t_spec      *specHandling(t_spec *specs, char *line)
{
    if (!line)
        return (NULL);
    if (line[0] == '1')
        return
    if (line[0] == 'N' && line[1] == 'O')
}
t_spec      *initSpec(char *pathToCub)
{
    int fd;
    int ret;
    char *line;
    t_spec *specs;

    if (!(specs = (t_spec*)malloc(sizeof(t_spec))))
        return (NULL);
    if(!(fd = (open(pathconf, O_RDONLY))))
        return (free_spec(specs));
    while((ret = get_next_line(fd, &line) == 1))
    {
        specs = specHandling(specs, line);
        free(line);
    }
}