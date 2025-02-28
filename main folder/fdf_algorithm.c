/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:19:09 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/28 19:31:36 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Determines the pixels color.
int rgb_to_int(double r, double g, double b)// double: high-precision floating-poimg or numbers (up to 15 to 17 digits)
{
	int color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    return (color);
}

// Distances the points from each other.
static void	ft_setscale(t_myimg *img, t_math *math)
{
	math->x *= img->zoom;
	math->y *= img->zoom;
	math->x1 *= img->zoom;
	math->y1 *= img->zoom;
}

//Applies isometric poxection.
void	ft_isometry(double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_x = *x;
	prev_y = *y;
	prev_z = *z;
	*x = (prev_x - prev_y) * cos(0.523599);//180^*(pi/180) == 3.14159 rad
	*y = (prev_x + prev_y) * sin(0.523599) - prev_z; //30^*(pi/180) == 0.523599 rad
	// z = prev_z * cos(0.523599) - prev_x * sin(0.523599);
}

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

// Algorithm to trace a line from xy to x1y1.
void	ft_bresenham(t_myimg *img, t_math *math, int color)
{
	math->z = img->map[(int)math->y][(int)math->x];
	math->z1 = img->map[(int)math->y1][(int)math->x1];
	ft_isometry(&math->x, &math->y, &math->z);//determinare il colore in ft_isometry?
	ft_isometry(&math->x1, &math->y1, &math->z1);
	ft_setscale(img, math);
	math->dx = fabs(math->x1 - math->x);
	math->dy = fabs(math->y1 - math->y);
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
		ft_bresenham(img, math, img->colmap[math->i][math->j]);
	}
	if (math->i < img->height - 1)
	{
		math->x = math->j;
		math->y = math->i;
		math->x1 = math->j;
		math->y1 = math->i + 1;
		ft_bresenham(img, math, img->colmap[math->i][math->j]);
	}
}

//Loops through each point on the map.
void	draw(t_myimg *img)
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
