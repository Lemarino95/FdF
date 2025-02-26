/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mapsizes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:34:58 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/26 16:47:25 by lemarino         ###   ########.fr       */
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
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		height++;
	}
	close(fd);
	return (height);
}

int	get_width(char *map_file)
{
	int		width;
	int		fd;
	int		i;
	char	*buf;
	char	*line;

	buf = NULL;
	line = ft_strdup("");
	i = 0;
	fd = open(map_file, O_RDONLY);
	while (1)
	{
		buf = ft_realoc(buf, i + 1, i + 2);
		read(fd, buf, 1);
		if (buf[0] == '\n')
			break ;
		line = ft_realoc(line, i + 1, i + 2);
		line[i] = buf[0];
		i++;
		line[i] = '\0';
	}
	width = count_words(line, ' ');
	close(fd);
	return (free(buf), free(line), width);
}
