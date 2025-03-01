/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_closure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:41:03 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/01 13:33:34 by lemarino         ###   ########.fr       */
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
	freemap(img->colmap, img);
	exit (0);
	return (0);
}

// Puts all pixels on the window to black (love to Amy W. <3)
void	ft_backtoblack(t_myimg *img)
{
	double	x;
	double	y;
	char	*dst;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_LEN)
		{
			dst = img->addr + ((int)y * img->line_length + \
							(int)x * (img->bits_per_pixel / 8));
			*(unsigned int *)dst = 000000;
			x++;
		}
		y++;
	}
}
