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
# define CUBE3D_H
# include "./get_next_line/get_next_line.h"
# include "mlx.h"

typedef	struct		s_spec
{
    int resX;
    int resY;
	char *pathNO;
	char *pathSO;
    char *pathEA;
    char *pathWE;
    int colorF;
    int colorC;
    char *pathS;
    char **map;
}					t_spec;

# endif