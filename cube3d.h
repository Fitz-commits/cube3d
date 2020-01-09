/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:07:33 by cdelaby           #+#    #+#             */
/*   Updated: 2019/12/16 16:07:35 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H
# include "./get_next_line/get_next_line.h"
# include "mlx.h"

typedef	struct		s_spec
{
    int resX;
    int resY;
    int posX;
    int posY;
    char orien;
	char *pathNO;
	char *pathSO;
    char *pathEA;
    char *pathWE;
    int colorF;
    int colorC;
    char *pathS;
    char **map;
}					t_spec;

t_spec		*free_spec(t_spec *specs);
int			ft_ar_to_int(char *color);
char		*ft_strnaddmod(char *rest, char *s2);
t_spec		*zero_spec(t_spec *specs);
t_spec      *spec_hand_bis(t_spec *specs, char **spl_l);
t_spec		*map_builder(t_spec *specs, char *line, int fd);
t_spec      *specHandling(t_spec *specs, char *line);
t_spec      *initSpec(char *pathToCub);
t_spec		*free_line(char *line);
t_spec		*free_map(char **map);
t_spec		*free_all_spec(t_spec *specs);
t_spec		*free_sp_spl(t_spec *specs, char **spl_l);
int         valid_map(char **map);

# endif