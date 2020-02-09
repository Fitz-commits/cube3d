/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 13:25:45 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 13:25:47 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			pr_err(char *error)
{
	if (error == NULL)
		return (0);
	ft_putstr_fd("Error\nCouldn't ", 1);
	ft_putstr_fd(error, 1);
	return (0);
}

t_spec		*pr_err_sp(char *error)
{
	ft_putstr_fd("Error\nCouldn't ", 1);
	ft_putstr_fd(error, 1);
	return (NULL);
}
