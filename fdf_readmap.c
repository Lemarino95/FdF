/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_readmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:29:27 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/04 15:56:08 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Converts the number of the map file in an int
int	map_setup(t_read *mapping, int **map, int i, int j)
{
	while (mapping->splitted_line[j])
		{
			map[i][j] = ft_atoi(mapping->splitted_line[j]);
			j++;
		}
	return (j);
}

// Converts the number following a comma in the map file in an int
static int	convert_hexa(t_read *mapping, int **map, int i, int j)
{
	if (ft_strchr2(mapping->splitted_line[j], 'x'))
		map[i][j] = ft_atoi_base \
					(ft_strchr2(mapping->splitted_line[j], 'x'), 16);
	else
		map[i][j] = 48127;
	return (1);
}

//Converts each number following a comma in the map file in an int and returns
// it as a matrix of color values.
static int	**col_mtrx_creator(t_read *mapper, int **map, t_myimg *img)
{
	t_read	mapping;
	int		i;
	int		j;

	i = 0;
	mapping.line = get_next_line(mapper->fd);
	while (mapping.line)
	{
		j = 0;
		map = ft_realoc(map, ((i) * sizeof(int *)), ((i + 1) * sizeof(int *)));
		mapping.line2 = ft_strtrim(mapping.line, "\n");
		mapping.splitted_line = ft_split(mapping.line2, ' ');
		if (i >= img->height)
			return (free_maputils(&mapping), map);
		map[i] = malloc(count_words(mapping.line2, ' ') * sizeof(int));
		if (!map[i])
			return (free(map[i]), free_maputils(&mapping), NULL);
		while (mapping.splitted_line[j])
			j += convert_hexa(&mapping, map, i , j);
		i++;
		free_maputils(&mapping);
		mapping.line = get_next_line(mapper->fd);
	}
	return (map);
}

//Converts each number of the map file in an int and returns it as
// a matrix of z-axis values.
static int	**z_mtrx_creator(t_read *mapper, int **map, t_myimg *img)
{
	t_read	mapping;
	int		i;
	int		j;

	i = 0;
	mapping.line = get_next_line(mapper->fd);
	if (!mapping.line)
		content_check(img);
	while (mapping.line)
	{
		j = 0;
		map = ft_realoc(map, ((i) * sizeof(int *)), ((i + 1) * sizeof(int *)));
		mapping.line2 = ft_strtrim(mapping.line, "\n");
		mapping.splitted_line = ft_split(mapping.line2, ' ');
		if (i >= img->height)
			return (free_maputils(&mapping), map);
		map[i] = malloc(count_words(mapping.line2, ' ') * sizeof(int));
		if (!map[i])
			return (free(map[i]), free_maputils(&mapping), NULL);
		j = map_setup(&mapping, map, i, j);
		i++;
		free_maputils(&mapping);
		mapping.line = get_next_line(mapper->fd);
	}
	return (map);
}

//Initializes and returns the map matrix.
int	**cartography(char *map_file, int select, t_myimg *img)
{
	t_read	mapper;
	int		**map;

	map = NULL;
	mapper.fd = open(map_file, O_RDONLY);
	permission_check(&mapper, img);
	if (select == 1)
		map = z_mtrx_creator(&mapper, map, img);
	else if (select == 2)
		map = col_mtrx_creator(&mapper, map, img);
	close (mapper.fd);
	return (map);
}
