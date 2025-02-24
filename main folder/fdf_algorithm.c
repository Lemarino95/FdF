/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:19:09 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/24 21:57:42 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Determines the pixels color.
int rgb_to_int(double r, double g, double b)// double: high-precision floating-point img or numbers (up to 15 to 17 digits)
{
	int color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    return (color);
}

// Distances the points from each other.
static void	ft_setscale(t_myimg *img, double *x0, double *y0, double *x1, double *y1)
{
	*x0 *= img->zoom;
	*y0 *= img->zoom;
	*x1 *= img->zoom;
	*y1 *= img->zoom;
}

//Applies isometric pojection.
void	ft_isometry(double *x, double *y, double z)
{
	double	prev_x = *x;
	double	prev_y = *y;
	
	*x = (prev_x - prev_y) * cos(0.523599);//90^*(pi/180) == 1,5708 rad
	*y = (prev_x + prev_y) * sin(0.523599) - z; //30^*(pi/180) == 0.523599 rad
}

// Determines in which direction the line is to be drawn.
static void	ft_setdirection(t_math *math, double x0, double y0, double x1, double y1)
{
	math->dir_x = 1;
	math->dir_y = 1;
	if (x0 > x1)
		math->dir_x = -1;
	if (y0 > y1)
		math->dir_y = -1;
}

// Algorithm to trace a line from x0y0 to x1y1.
void    ft_bresenham(t_myimg *img, double x0, double y0, double x1, double y1, int color)
{
	t_math	math;

	ft_isometry(&x0, &y0, img->map[(int)y0][(int)x0]);//determinare il colore in ft_isometry?
	ft_isometry(&x1, &y1, img->map[(int)y1][(int)x1]);
	ft_setscale(img, &x0, &y0, &x1, &y1);
	math.dx = fabs(x1 - x0);
	math.dy = fabs(y1 - y0);
	math.err = math.dx - math.dy;
	ft_setdirection(&math, x0, y0, x1, y1);
	if (math.dir_x > 0 && math.dir_y > 0)
		to_northwest(x0, x1, y0, y1, *img, &math, color);
	else if (math.dir_x > 0 && math.dir_y < 0)
		to_northeast(x0, x1, y0, y1, *img, &math, color);
	else if (math.dir_x < 0 && math.dir_y > 0)
		to_southwest(x0, x1, y0, y1, *img, &math, color);
	else if (math.dir_x < 0 && math.dir_y < 0)
		to_southeast(x0, x1, y0, y1, *img, &math, color);
}

void	draw(t_myimg *img)
{
	double	x;
	double	y;
	double	x1;
	double	y1;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		y1 = y +1;
		while (x < img->width)
		{
			x1 = x + 1;
			if (x < img->width - 1)
				ft_bresenham(img, x, y, x1, y, img->colmap[(int)y][(int)x]);
				// ft_bresenham(img, x, y, x + 1, y, rgb_to_int(0, 187, 255));
			if (y < img->height - 1)
				ft_bresenham(img, x, y, x, y1, img->colmap[(int)y][(int)x]);
				// ft_bresenham(img, x, y, x, y + 1, rgb_to_int(63, 210, 66));
			x++;
		}
		y++;
	}
}
