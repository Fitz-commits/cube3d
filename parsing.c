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

t_spec      *specHandling(t_spec *specs, char *line)
{
    if (!line)
        return (NULL);
    if ()
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
        return (NULL);
    while((ret = get_next_line(fd, &line) == 1))
    {
        specs = specHandling(specs, line);
        free(line);
    }
}