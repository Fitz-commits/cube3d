/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:07:33 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/10 13:21:28 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# include "./libft/libft.h"
# include "./minilibx_opengl/mlx.h"
# include <math.h>

# define K_W 13
# define K_S 1
# define K_A 0
# define K_D 2
# define K_LEFT 123
# define K_RIGHT 124
# define K_ESC 53
# define MOVESPEED 0.20
# define ROTSPEED 0.1

typedef	struct	s_text
{
	void		**vtext;
	char		**chartext;
	int			**itext;
	int			theight[5];
	int			twidth[5];
	int			tsl[5];
	int			bpp[5];
	int			med[5];
}				t_text;

typedef	struct	s_sprite
{
	double		*sprite_x;
	double		*sprite_y;
}				t_sprite;

typedef	struct	s_up
{
	char		key_w;
	char		key_s;
	char		key_a;
	char		key_d;
	char		key_left;
	char		key_right;
	char		key_exit;
}				t_up;

typedef	struct	s_spec
{
	int			save;
	void		*mlx;
	void		*win_ptr;
	int			x;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	double		tex_pos;
	double		step;
	void		*imgptr;
	char		*charimgptr;
	int			res_x;
	int			res_y;
	char		orien;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	int			color_f;
	int			color_c;
	char		*path_s;
	char		**map;
	int			*intimgptr;
	t_text		*text;
	int			sprite_nb;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		trans_x;
	double		trans_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			tex_y;
	int			tex_x;
	int			s_color;
	int			stripe;
	int			d;
	int			y;
	t_sprite	*sprites;
	t_up		*up;

}				t_spec;

/*
** bmp.c
*/
int				save_bmp(t_spec *inf);
/*
** dda.c
*/
void			set_side_step(t_spec *inf);
void			perf_dda(t_spec *inf);
void			set_draw(t_spec *inf);
void			put_pixel_img(t_spec *inf, double *zbuf);
void			dda_setup(t_spec *inf);
/*
** draw.c
*/
void			draw_inside(t_spec *inf, int draw_s, int draw_e, int tex_num);
void			sprite_drawing(t_spec *inf);
int				draw(t_spec *inf);
/*
** free_ft_bis.c
*/
void			free_sprites(t_sprite *sprites);
t_text			*free_text(t_spec *inf);
t_spec			*free_all_spec(t_spec *specs, char *error);
t_text			*free_all_spect(t_spec *specs, char *error);
t_spec			*free_sp_spl(t_spec *specs, char **spl_l, char *error);
/*
** free_ft.c
*/
t_spec			*free_spec(t_spec *specs);
t_text			*free_spect(t_spec *specs);
t_spec			*free_line(char *line);
char			*free_line_char(char *line);
t_spec			*free_map(char **map);
/*
** ft_error.c
*/
int				pr_err(char *error);
t_spec			*pr_err_sp(char *error);
/*
** key_handling.c
*/
void			move_left(t_spec *inf);
void			move_right(t_spec *inf);
void			move_forward(t_spec *inf);
void			move_backward(t_spec *inf);
/*
** key_up.c
*/
int				key_update(t_spec *inf);
int				key_hook(int key, void *param);
int				ft_close(t_spec *inf);
t_spec			*zero_up(t_spec *specs);
/*
** main.c
*/
t_spec			*init_cube(t_spec *inf);
void			set_img(t_spec *inf);
t_spec			*init_spec(char *path_to_cub);
/*
** math.c
*/
void			rotate_left(t_spec *inf);
void			rotate_right(t_spec *inf);
int				ft_ar_to_int(char *color);
/*
** parsing.c
*/
char			*addbackn(char *line);
char			**delete_space(char **map, int i);
t_spec			*spec_hand_bis(t_spec *specs, char **spl_l);
t_spec			*map_builder(t_spec *specs, char *line, int fd);
t_spec			*spec_handling(t_spec *specs, char *line);
/*
** process_map.c
*/
t_spec			*set_dir(t_spec *inf, double dir_x, double dir_y);
t_spec			*set_plane(t_spec *inf, double plane_x, double plane_y);
t_spec			*set_player(t_spec *inf);
/*
** sprite_init.c
*/
int				get_sprite_number(char **map);
t_sprite		*zeroing_sprite(t_sprite *sprites);
t_sprite		*catch_sprite(t_spec *inf, int i);
void			sprite_math(t_spec *inf, int i);
void			sprite_set(t_spec *inf, double *z_buffer);
/*
** sprite_sort.c
*/
double			*cacl_dist(t_spec *inf);
void			swap_sprite(t_spec *inf, int i, int j);
t_sprite		*buble_sort_sprite(t_spec *inf);
/*
** tex_handling.c
*/
t_text			*zeroing(t_text *text);
t_text			*init_void(t_spec *inf);
void			set_texture(t_spec *inf);
t_text			*get_adress(t_text *text);
/*
** utils.c
*/
int				valid_map(char **map);
t_spec			*set_oxy(t_spec *inf, char o, int y, int x);
t_spec			*get_letter(t_spec *inf);
t_spec			*zero_spec(t_spec *specs);
char			*ft_strnaddmod(char *rest, char *s2);

#endif
