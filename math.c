/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 08:16:51 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/08 08:16:56 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>
int         ft_ar_to_int(char *color)
{
    int r;
    int g;
    int b;
    int colorhex;
    
    r = ft_atoi(color);
    g = ft_atoi(&color[get_size(r, 10) + 1]);
    b = ft_atoi(&color[get_size(r, 10) + get_size(g, 10) + 2]);
    colorhex = r * 256 * 256 + g * 256 + b;
    return (colorhex);
}

/*int main()
{
    printf("%d", ft_ar_to_int("255,0,154"));
}*/