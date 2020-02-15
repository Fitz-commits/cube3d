/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:49:31 by cdelaby           #+#    #+#             */
/*   Updated: 2020/02/09 19:33:38 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char			*addbackn(char *line)
{
	char *buffer;
	char *cpy;
	char *cpy_buf;

	if (!(buffer = (char*)(malloc(ft_strlen(line) + 2))))
	{
		pr_err("alloc buffer in addbackn");
		return (free_line_char(line));
	}
	cpy_buf = buffer;
	cpy = line;
	while (*line)
		*buffer++ = *line++;
	*buffer++ = '\n';
	*buffer = '\0';
	free(cpy);
	return (cpy_buf);
}

char			**delete_space(char **map, int i)
{
	int			j;
	char		*temp;
	char		*tempcp;
	int			space;

	while (map[i])
	{
		space = 0;
		j = 0;
		while (map[i][j])
			if (map[i][j++] == ' ' || map[i][j++] == '\t')
				space += 1;
		if (!(temp = (char*)malloc(ft_strlen(map[i]) - space + 1)))
			return (NULL);
		tempcp = temp;
		j = 0;
		while (map[i][j++])
			if (map[i][j - 1] != ' ' || map[i][j++] != '\t')
				*tempcp++ = map[i][j - 1];
		*tempcp = '\0';
		free(map[i]);
		map[i++] = temp;
	}
	return (map);
}

t_spec			*spec_hand_bis(t_spec *specs, char **spl_l)
{
	int temp_x;
	int temp_y;

	if (!(ft_strncmp(spl_l[0], "F", 1)))
		specs->color_f = ft_ar_to_int(spl_l[1]);
	if (!(ft_strncmp(spl_l[0], "C", 1)))
		specs->color_c = ft_ar_to_int(spl_l[1]);
	if (!(ft_strncmp(spl_l[0], "R", 1)))
	{
		temp_x = ft_atoi(spl_l[1]);
		temp_y = ft_atoi(spl_l[2]);
		if (temp_x > 1920)
			temp_x = 1920;
		if (temp_x < 480)
			temp_x = 480;
		if (temp_y > 1080)
			temp_y = 1080;
		if (temp_y < 360)
			temp_y = 360;
		specs->res_x = temp_x;
		specs->res_y = temp_y;
	}
	free_map(spl_l);
	return (specs);
}

t_spec			*map_builder(t_spec *specs, char *line, int fd)
{
	char		*buffer;
	int			ret;

	buffer = addbackn(line);
	while ((ret = get_next_line(fd, &line) == 1))
	{
		if (!(buffer = ft_strnaddmod(buffer, line)))
			return (free_line(line));
		free(line);
	}
	free(line);
	if (!(specs->map = ft_split(buffer, '\n')))
		return (free_line(buffer));
	free_line(buffer);
	return (specs);
}

t_spec			*spec_handling(t_spec *specs, char *line)
{
	char **spl_l;

	if (line[0] == '\0')
		return (specs);
	if (!(spl_l = ft_split(line, ' ')))
		return (free_spec(specs));
	if (!specs->path_no && (!(ft_strncmp(spl_l[0], "NO", 2))))
		if (!(specs->path_no = ft_strdup(spl_l[1])))
			return (free_sp_spl(specs, spl_l, "alloc path_no"));
	if (!specs->path_so && !(ft_strncmp(spl_l[0], "SO", 2)))
		if (!(specs->path_so = ft_strdup(spl_l[1])))
			return (free_sp_spl(specs, spl_l, "alloc path_so"));
	if (!specs->path_we && !(ft_strncmp(spl_l[0], "WE", 2)))
		if (!(specs->path_we = ft_strdup(spl_l[1])))
			return (free_sp_spl(specs, spl_l, "alloc path_we"));
	if (!specs->path_ea && !(ft_strncmp(spl_l[0], "EA", 2)))
		if (!(specs->path_ea = ft_strdup(spl_l[1])))
			return (free_sp_spl(specs, spl_l, "alloc path_ea"));
	if (!specs->path_s && !(ft_strncmp(spl_l[0], "S", 1)) && spl_l[0][1] == 0)
		if (!(specs->path_s = ft_strdup(spl_l[1])))
			return (free_sp_spl(specs, spl_l, "alloc path_s"));
	return (spec_hand_bis(specs, spl_l));
}
