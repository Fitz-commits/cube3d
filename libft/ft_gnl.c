/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:31:16 by cdelaby           #+#    #+#             */
/*   Updated: 2020/01/27 13:31:19 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			search_buf(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == 10)
			return (i);
		i++;
	}
	return (-1);
}

static int			handle_rest(char **line, char *rest)
{
	int is_rest;

	is_rest = (rest[0] == 0) ? 0 : 1;
	if (search_buf(rest) == -1)
	{
		*line = ft_strdup(rest);
		rest[0] = 0;
		return (is_rest);
	}
	if (search_buf(rest) + 1 == ft_strlen(rest))
		is_rest = -1;
	*line = ft_strndup(rest, search_buf(rest));
	ft_strcpy(rest, &rest[search_buf(rest) + 1]);
	return (is_rest);
}

static int			post_checks_gnl(int fd, char **line)
{
	static char		rest[OPEN_MAX][BUFFER_SIZE + 1] = {{0}};
	char			buf[BUFFER_SIZE + 1];
	int				br;
	int				is_rest;

	br = 1;
	if (((is_rest = handle_rest(line, rest[fd])) == -1))
		return (1);
	while ((rest[fd][0] == 0) && ((br = read(fd, buf, BUFFER_SIZE)) > 0))
	{
		buf[br] = 0;
		if (search_buf(buf) != -1)
		{
			ft_strcpy(rest[fd], &buf[search_buf(buf) + 1]);
			buf[search_buf(buf)] = 0;
			*line = ft_stradd(*line, buf);
			return (1);
		}
		*line = ft_stradd(*line, buf);
	}
	if (is_rest && br)
		return (1);
	return ((br == -1) ? -1 : 0);
}

int					get_next_line(int fd, char **line)
{
	if (BUFFER_SIZE <= 0)
		return (-1);
	else if (fd < 0 || fd > OPEN_MAX || line == NULL)
		return (-1);
	else
		return (post_checks_gnl(fd, line));
}
