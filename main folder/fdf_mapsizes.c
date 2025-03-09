/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mapsizes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:34:58 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/05 16:46:55 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_composeline(char *buf, char *line, int fd)
{
	int	i;
	int	width;

	i = 0;
	while (1)
	{
		buf = ft_realoc(buf, i + 1, i + 2);
		if (!buf)
			return (free(buf), 0);
		read(fd, buf, 1);
		if (buf[0] == '\n')
			break ;
		line = ft_realoc(line, i + 1, i + 2);
		if (!line)
			return (free(line), 0);
		line[i] = buf[0];
		i++;
		line[i] = '\0';
	}
	width = count_words(line, ' ');
	return (free(buf), free(line), width);
}

int	get_width(char *map_file)
{
	int		width;
	int		fd;
	char	*buf;
	char	*line;

	buf = NULL;
	line = ft_strdup("");
	if (!line)
		return (0);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (free(line), 0);
	width = ft_composeline(buf, line, fd);
	close(fd);
	return (width);
}

int	get_height(char *map_file)
{
	int		height;
	int		fd;
	char	*line;

	height = 0;
	fd = open(map_file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line || line[0] == '\n')
		{
			free(line);
			break ;
		}
		if (count_words(line, ' ') == 0)
		{
			free(line);
			continue ;
		}
		free(line);
		height++;
	}
	close(fd);
	return (height);
}
