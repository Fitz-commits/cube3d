/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:42:11 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/08 09:42:12 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (fd > 0)
	{
		if (nb == -2147483648)
		{
			ft_putchar_fd('-', fd);
			write(fd, "2147483648", 10);
		}
		else
		{
			if (nb < 0)
			{
				ft_putchar_fd('-', fd);
				nb = nb * -1;
			}
			if (nb > 9)
			{
				ft_putnbr_fd((nb / 10), fd);
				ft_putchar_fd(((nb % 10) + 48), fd);
			}
			else
				ft_putchar_fd((nb + 48), fd);
		}
	}
}
