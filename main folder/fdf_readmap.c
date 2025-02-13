/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_readmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:29:27 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/13 22:00:00 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_words(const char *str, char c)
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

static char	**freemtrx(char **s)
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

int	**cartography(char *map_file)
{
	t_read	mapping;
	int		i;
	int		j;
	int		**map;

	i = 0;
	map = malloc(sizeof(int *));
	mapping.fd = open(map_file, O_RDONLY);
	while ((mapping.line = get_next_line(mapping.fd)) != NULL)
	{
		j = 0;
		map = realloc(map, (i * sizeof(int *) + 1));
		mapping.line = ft_strtrim(mapping.line, "\n");//basta fare malloc(** -1)?
		mapping.splitted_line = ft_split(mapping.line, ' ');
		map[i] = malloc(count_words(mapping.line, ' ') * sizeof(int));
		while (mapping.splitted_line[j])
		{
			map[i][j] = ft_atoi(mapping.splitted_line[j]);
			j++;
		}
		i++;
	}
	freemtrx(mapping.splitted_line);
	close (mapping.fd);
	return (free(mapping.line), map);
}

/* int	main(int argc, char *argv[])
{
	int i = 0;
	int j;
	int **map= cartography(argv[1]);
	if (argc > 1)
	{
		while (i < 11)
		{
			j = 0;
			while (j < 19)
				{
					printf("%d", map[i][j]);
					j++;
					printf(" ");
				}
			printf("\n");
			i++;
		}
	}
} */