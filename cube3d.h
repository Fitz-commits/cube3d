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

# define K_W 13
# define K_S 1
# define K_A 0
# define K_D 2
# define K_LEFT 123
# define K_RIGHT 124
# define K_ESC 53
# define moveSpeed 0.1
# define rotSpeed 3.141592653589793238462643383279502884197169399375105820974/64

typedef	struct		s_spec
{
    int time;
    int oldTime;
    void *imgptr;
    char *charimgptr;
    void *mlx;
    void *win_ptr;
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    int resX;
    int resY;
    char orien;
	char *pathNO;
	char *pathSO;
    char *pathEA;
    char *pathWE;
    int colorF;
    int colorC;
    char *pathS;
    char **map;
    char *text1;
    char *vtext1;
    int *intimgptr;
    int  twidth;
	int  theight;
    int *ptrtext;
}					t_spec;
//lis la map et store dans une structure
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
char		*free_line_char(char *line);
// check si mur == 1
int         valid_map(char **map);
//set dirX dirY planeX planeY en fonction de la map
t_spec		*set_oxy(t_spec *inf, char o, int y, int x);
t_spec		*get_letter(t_spec *inf);
t_spec		*set_dir(t_spec *inf, double dirX, double dirY);
t_spec		*set_plane(t_spec *inf, double planeX, double planeY);
t_spec		*set_player(t_spec *inf);
int         verLine(t_spec *inf, int draw_start, int draw_end, int x, int color);

# endif