/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mapsizes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:34:58 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/19 15:37:38 by lemarino         ###   ########.fr       */
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
	char	*line;

	width = 0;
	fd = open(map_file, O_RDONLY);
	line = get_next_line(fd);
	width = count_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}
