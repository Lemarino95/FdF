/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error_controls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:33:04 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/06 12:33:35 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	extension_check(char *filename)
{
	if (!(ft_strrcmp(filename, "x.fdf", 4)))
	{
		perror(RED"ERROR: invalid map extension"NO_COLOR);
		exit(0);
		return (0);
	}
	return (1);
}

int	arg_check(int ac, char **av)
{
	int	flag;

	flag = 0;
	if (ac != 2)
	{
		perror(RED"ERROR: Invalid number of arguments"NO_COLOR);
		exit(0);
		return (0);
	}
	flag += extension_check(av[1]);
	return (flag);
}

void	sizes_check(t_myimg *img)
{
	if (img->height == 0 || img->width == 0)
	{
		perror(RED"Couldn't generate map."NO_COLOR);
		close_all(img);
	}
	return ;
}

void	permission_check(t_read *mapper, t_myimg *img)
{
	if (mapper->fd < 0)
	{
		perror(RED"ERROR: Permission denied or .fdf file not found"NO_COLOR);
		mlx_destroy_image(img->mlx_ptr, img->nimg);
		mlx_destroy_window(img->mlx_ptr, img->mlx_win);
		mlx_destroy_display(img->mlx_ptr);
		free(img->mlx_ptr);
		exit (0);
	}
}

void	content_check(t_myimg *img)
{
	perror(RED"File is empty."NO_COLOR);
	close_all(img);
}
