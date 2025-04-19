/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix_creators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:03:02 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/05 22:03:30 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Converts the number following a comma in the map file in an int
static void	convert_hexa(t_read *mapping, int **map, int i)
{
	int		j;

	j = 0;
	while (mapping->splitted_line[j])
	{
		if (ft_strchr2(mapping->splitted_line[j], 'x'))
			map[i][j] = ft_atoi_base \
						(ft_strchr2(mapping->splitted_line[j], 'x'), 16);
		else
			map[i][j] = 10143743;
		j++;
	}
	return ;
}

//Converts each number following a comma in the map file in an int and returns
// it as a matrix of color values.
int	**col_mtrx_creator(t_read *mapper, int **map, t_myimg *img)
{
	t_read	mapping;
	int		i;

	i = 0;
	mapping.line = get_next_line(mapper->fd);
	while (mapping.line)
	{
		map = ft_realoc(map, ((i) * sizeof(int *)), ((i + 1) * sizeof(int *)));
		mapping.line2 = ft_strtrim(mapping.line, "\n");
		mapping.splitted_line = ft_split(mapping.line2, ' ');
		if (i >= img->height)
			return (free_maputils(&mapping), map);
		if (count_words(mapping.line2, ' ') >= img->width)
			map[i] = ft_calloc(count_words(mapping.line2, ' '), sizeof(int));
		else
			map[i] = ft_calloc(img->width, sizeof(int));
		if (!map[i])
			return (free(map[i]), free_maputils(&mapping), NULL);
		convert_hexa(&mapping, map, i);
		i++;
		free_maputils(&mapping);
		mapping.line = get_next_line(mapper->fd);
	}
	return (map);
}

//Converts the number of the map file in an int
static void	map_setup(t_read *mapping, int **map, int i, t_myimg *img)
{
	int	j;

	j = 0;
	mapping->splitted_line = ft_split(mapping->line2, ' ');
	if (count_words(mapping->line2, ' ') >= img->width)
		map[i] = ft_calloc(count_words(mapping->line2, ' '), sizeof(int));
	else
		map[i] = ft_calloc(img->width, sizeof(int));
	if (!map[i])
		return (free_maputils(mapping));
	while (mapping->splitted_line[j])
	{
		map[i][j] = ft_atoi(mapping->splitted_line[j]);
		j++;
	}
	free_maputils(mapping);
	return ;
}

//Converts each number of the map file in an int and returns it as
// a matrix of z-axis values.
int	**z_mtrx_creator(t_read *mapper, int **map, t_myimg *img)
{
	t_read	mapping;
	int		i;

	i = 0;
	mapping.line = get_next_line(mapper->fd);
	if (!mapping.line)
		content_check(img);
	while (mapping.line)
	{
		map = ft_realoc(map, ((i) * sizeof(int *)), ((i + 1) * sizeof(int *)));
		mapping.line2 = ft_strtrim(mapping.line, "\n");
		if (!mapping.line2)
			return (NULL);
		if (i >= img->height)
			return (free(mapping.line2), map);
		map_setup(&mapping, map, i, img);
		if (!map[i])
			return (free(map[i]), free_maputils(&mapping), NULL);
		i++;
		mapping.line = get_next_line(mapper->fd);
	}
	return (map);
}
