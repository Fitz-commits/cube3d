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
# include "./libft/libft.h"
# include "mlx.h"

# define K_W 13
# define K_S 1
# define K_A 0
# define K_D 2
# define K_LEFT 123
# define K_RIGHT 124
# define K_ESC 53
# define moveSpeed 0.20
# define rotSpeed 3.141592653589793238462643383279502884197169399375105820974/32


typedef		struct s_text
{
	void **vtext;
	char **chartext;
	int **itext;
	int theight[5];
	int twidth[5];
	int tsl[5];
	int bpp[5];
	int med[5];
}					t_text;

typedef		struct s_sprite
{
    double *sprite_x;
    double *sprite_y;
}					t_sprite;

typedef	struct		s_spec
{
    void *mlx;
    void *win_ptr;
    int x;
    // dda
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
    double wall_x;

    double texPos;
    double step;
    int texX;
    void *imgptr;
    char *charimgptr;
    int res_x;
    int res_y;
    char orien;
	char *pathNO;
	char *pathSO;
    char *pathEA;
    char *pathWE;
    int colorF;
    int colorC;
    char *pathS;
    char **map;
    int *intimgptr;
	t_text *text;
    //sprite handling;
    int sprite_nb;
    double sprite_x;
    double sprite_y;
    double inv_det;
    double trans_x;
    double trans_y;
    int sprite_screen_x;
    int sprite_height;
    int draw_start_y;
    int draw_end_y;
    int sprite_width;
    int draw_start_x;
    int draw_end_x;
    int tex_y;
    int tex_x;


    t_sprite *sprites;
}					t_spec;

// vtext représente l'image destroy it if need be
// char_text = addresse de l'image pour modification
// itext valeur utilisee dans les calculs

//lis la map et store dans une structure
int			save_bmp(t_spec *inf);
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

// texture 

t_text	*init_void(t_spec *inf);
t_text	*get_adress(t_text *text);

// sprites

t_sprite	*catchSprite(t_spec *inf);
t_sprite	*buble_sort_sprite(t_spec *inf);
# endif