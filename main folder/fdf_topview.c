/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_topview.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:08:51 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/06 12:57:09 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Determines in which direction the line is to be drawn.
static void	ft_setdirection(t_math *math)
{
	math->dir_x = 1;
	math->dir_y = 1;
	if (math->x > math->x1)
		math->dir_x = -1;
	if (math->y > math->y1)
		math->dir_y = -1;
}

// main body of the algorithm to trace a line from xy to x1y1.
static void	bresenham(t_myimg *img, t_math *math, int color)
{
	math->z = img->map[(int)math->y][(int)math->x];
	math->z1 = img->map[(int)math->y1][(int)math->x1];
	rotate_coords(img, math);
	ft_setscale(img, math);
	math->dx = fabs(math->x1 - math->x);
	math->dy = fabs(math->y1 - math->y);
	if (math->dx == 0 && math->dy == 0)
		return ;
	math->err = math->dx - math->dy;
	ft_setdirection(math);
	if (math->dir_x > 0 && math->dir_y > 0)
		to_northwest(*img, math, color);
	else if (math->dir_x > 0 && math->dir_y < 0)
		to_northeast(*img, math, color);
	else if (math->dir_x < 0 && math->dir_y > 0)
		to_southwest(*img, math, color);
	else if (math->dir_x < 0 && math->dir_y < 0)
		to_southeast(*img, math, color);
}

//Applies an alghorithm to print and connect the current point to those 
// on the right and below.
static void	draw2(t_myimg *img, t_math *math)
{
	if (math->j < img->width - 1)
	{
		math->x = math->j;
		math->y = math->i;
		math->x1 = math->j + 1;
		math->y1 = math->i;
		if (img->colmap[math->i][math->j])
			bresenham(img, math, img->colmap[math->i][math->j]);
	}
	if (math->i < img->height - 1)
	{
		math->x = math->j;
		math->y = math->i;
		math->x1 = math->j;
		math->y1 = math->i + 1;
		if (img->colmap[math->i][math->j])
			bresenham(img, math, img->colmap[math->i][math->j]);
	}
}

//Loops through each point on the map.
static void	draw_noisometry(t_myimg *img)
{
	t_math	math;

	math.i = 0;
	while (math.i < img->height)
	{
		math.j = 0;
		while (math.j < img->width)
		{
			draw2(img, &math);
			math.j++;
		}
		math.i++;
	}
}

void	set_topview(t_myimg *img)
{
	img->angle_x = -0.003179;
	img->angle_y = 0.000001;
	img->angle_z = 0.002346;
	ft_backtoblack(img);
	draw_noisometry(img);
	mlx_do_sync(img->mlx_ptr);
	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
}
