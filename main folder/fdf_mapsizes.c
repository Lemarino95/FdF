/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mapsizes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:34:58 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/21 19:44:50 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *map_file)
{
	int		height;
	int		fd;
	char	*line;

	height = 0;
	fd = open(map_file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	get_width(char *map_file)
{
	int		width;
	int		fd;
	int 	i;
	char	*buf;
	char	*line;

	buf = NULL;
	line = NULL;
	i = 0;
	fd = open(map_file, O_RDONLY);
	while (1)
	{
		buf = ft_realloc(buf, i + 2);
		read(fd, buf, 1);
		if (buf[0] == '\n')
			break;
		line = ft_realloc(line, i + 2);
		line[i] = buf[0];
		i++;
		line[i] = '\0';
	}
	width = count_words(line, ' ');
	close(fd);
	return (free(buf), free(line), width);
}
