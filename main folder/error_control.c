/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:33:04 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/01 18:31:57 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	extension_check(char *filename)
{
	if (!(ft_strrcmp(filename, "x.fdf", 4)))
	{
		perror(RED"ERR: invalid map extension."NO_COLOR);
		exit(0);
		return (0);
	}
	return (1);
}

int	arg_num_check(int ac, char **av)
{
	int	flag;

	flag = 0;
	if (ac != 2)
	{
		perror(RED"ERR: invalid number of arguments."NO_COLOR);
		exit(0);
		return (0);
	}
	flag += extension_check(av[1]);
	return (flag);
}

void	permission_check(t_read *mapper, t_myimg *img)
{
	if (mapper->fd < 0)
	{
		perror(RED"ERR: Permission denied by .fdf file."NO_COLOR);
		mlx_destroy_image(img->mlx_ptr, img->nimg);
		mlx_destroy_window(img->mlx_ptr, img->mlx_win);
		mlx_destroy_display(img->mlx_ptr);
		free(img->mlx_ptr);
		exit (0);
	}
}
