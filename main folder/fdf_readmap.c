/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_readmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:29:27 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/05 22:03:50 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_maputils(t_read *mapping)
{
	free(mapping->line2);
	freesplit(mapping->splitted_line);
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
