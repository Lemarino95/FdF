/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_readmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:29:27 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/22 11:39:56 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			words++;
		while (str[i] && str[i] != c)
		{
			i++;
		}
	}
	return (words);
}

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

//Converts each number of the map file in an int and returns it as
// a matrix of z-axis values.
static int **mtrx_creator(t_read *mapper, int **map)
{
	t_read	mapping;
	int		i;
	int		j;
	i = 0;
	
	mapping.line = get_next_line(mapper->fd);
	while (mapping.line)
	{
		j = 0;
		map = ft_realloc(map, ((i + 1) * sizeof(int *)));
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
int	**cartography(char *map_file)
{
	t_read	mapper;
	int		**map;

	map = NULL;
	mapper.fd = open(map_file, O_RDONLY);
	map = mtrx_creator(&mapper, map);
	close (mapper.fd);
	return (map);
}

/* int	main(int argc, char *argv[])
{
	int i = 0;
	int j;
	int **map= cartography(argv[1]);
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