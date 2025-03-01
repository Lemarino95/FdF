/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_readmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:29:27 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/01 15:39:23 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**freesplit(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static int	convert_hexa(char *str)
{
	if (ft_strchr2(str, 'x'))
		return (ft_atoi_base(ft_strchr2(str, 'x'), 16));
	else
		return (48127);
}

//Converts each number following a comma in the map file in an int and returns
// it as a matrix of color values.
int	**col_mtrx_creator(t_read *mapper, int **map)
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
		map[i] = malloc(count_words(mapping.line2, ' ') * sizeof(int));
		while (mapping.splitted_line[j])
		{
			map[i][j] = convert_hexa(mapping.splitted_line[j]);
			j++;
		}
		i++;
		free(mapping.line2);
		freesplit(mapping.splitted_line);
		mapping.line = get_next_line(mapper->fd);
	}
	return (map);
}

//Converts each number of the map file in an int and returns it as
// a matrix of z-axis values.
int	**z_mtrx_creator(t_read *mapper, int **map)
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
		map[i] = malloc(count_words(mapping.line2, ' ') * sizeof(int));
		while (mapping.splitted_line[j])
		{
			map[i][j] = ft_atoi(mapping.splitted_line[j]);
			j++;
		}
		i++;
		free(mapping.line2);
		freesplit(mapping.splitted_line);
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
	/* if (mapper.fd < 0)
	{
		perror(RED"ERR: Permission denied by .fdf file."NO_COLOR);
		close_all(img);
		return (0);
	} */
	permission_check(&mapper, img);
	if (select == 1)
		map = z_mtrx_creator(&mapper, map);
	else if (select == 2)
		map = col_mtrx_creator(&mapper, map);
	close (mapper.fd);
	return (map);
}

/* int	main(int argc, char *argv[])
{
	int i = 0;
	int j;
	int **map= cartography(argv[1], 2);
	int	height = get_height(argv[1]);
	int width = get_width(argv[1]);
	printf("%d*%d\n", height, width);
	if (argc > 1)
	{
		while (i < height)
		{
			j = 0;
			while (j < width)
				{
					printf("%2d", map[i][j]);
					j++;
					printf(" ");
				}
			printf("\n");
			i++;
		}
	}
} */