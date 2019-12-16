/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 07:53:16 by cdelaby           #+#    #+#             */
/*   Updated: 2019/11/04 10:58:07 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# define BUFFER_SIZE 16
int				search_buf(char *buf)
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

char			*ft_strnadd(char *rest, char *s2)
{
	char			*copy;
	char			*copy_cpp;
	char			*rest_cpp;

	if (rest == NULL)
		return (ft_strdup(s2));
	copy = ft_strdup(rest);
	free(rest);
	copy_cpp = copy;
	if (!(rest = (char*)malloc(sizeof(char) * (ft_strlen(copy)
						+ ft_strlen(s2) + 1)) ))
		return (0);
	rest_cpp = rest;
	while (*copy)
		*rest++ = *copy++;
	while (*s2)
		*rest++ = *s2++;
	free(copy_cpp);
	*rest = 0;
	return (rest_cpp);
}

int				handle_rest(char **line, char *rest)
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

int				post_checks_gnl(int fd, char **line)
{
	static char		rest[OPEN_MAX][BUFFER_SIZE + 1] = {{0}};
	char		buf[BUFFER_SIZE + 1];
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
			*line = ft_strnadd(*line, buf);
			return (1);
		}
		*line = ft_strnadd(*line, buf);
	}
	if (is_rest && br)
		return (1);
	return ((br == -1) ? -1 : 0);
}

int				get_next_line(int fd, char **line)
{
	if (BUFFER_SIZE <= 0)
		return (-1);
	else if (fd < 0 || fd > OPEN_MAX || line == NULL)
		return (-1);
	else
		return (post_checks_gnl(fd, line));
}
/*
int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*line;
	int		ret;

	printf("limit fdmax %d\n", OPEN_MAX); 
	if (argc != 2)
	{
		printf("You forgot the filename");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	i = 1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		printf("%3d [%s]\n", i, line);
		free(line);
		i++;
	}
	printf("%3d [%s]\n", i, line);
	free(line);
	if (ret == -1)
		printf("error\n");
	else if (ret == 0)
		printf("EOF\n");
	close(fd);
	return (0);
}
*/