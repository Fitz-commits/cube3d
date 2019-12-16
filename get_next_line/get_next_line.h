/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:23:32 by cdelaby           #+#    #+#             */
/*   Updated: 2019/12/12 14:11:52 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "../libft/libft.h"

int			search_buf(char *buf);
char		*ft_strnadd(char *rest, char *s2);
int			handle_rest(char **line, char *rest);
int			get_next_line(int fd, char **line);
int			post_checks_gnl(int fd, char **line);

#endif
