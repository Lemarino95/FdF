/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_closure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:41:03 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/22 20:28:31 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*~~~~~~~~~~~Functions to close the program and free memory~~~~~~~~~~~*/
//Frees the int matrix
static void	freemap(int **map, t_myimg *img)
{
	int	i;

	i = 0;
	while (i < img->height)
	{
		free(map[i]);
		i++;
	}
	free(map);
	return ;
}

int	close_all(t_myimg *img)
{
	mlx_destroy_image(img->mlx_ptr, img->nimg);
	mlx_destroy_window(img->mlx_ptr, img->mlx_win);
	mlx_destroy_display(img->mlx_ptr);
	free(img->mlx_ptr);
	freemap(img->map, img);
	exit (0);
	return (0);
}

void ft_backtoblack(t_myimg *img)// vedere mlx_dosync()
{
	double	x;
	double	y;

	/*printf(RED"CANCELLIAMO?"NO_COLOR);//##############
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (x < img->width - 1)
				ft_bresenham(img, x, y, x + 1, y, rgb_to_int(00, 00, 00));
			if (y < img->height - 1)
				ft_bresenham(img, x, y, x, y + 1, rgb_to_int(00, 00, 00));
			x++;
		}
		y++;
	}*/
	double	x;
	double	y;
	char	*dst;

	printf(RED"CANCELLIAMO?"NO_COLOR);//##############
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_LEN)
		{
			dst = img->addr + ((int)y * img->line_length + (int)x * (img->bits_per_pixel / 8));
			*(unsigned int*)dst = rgb_to_int(0, 0, 0);
			x++;
		}
		y++;
	}
}
