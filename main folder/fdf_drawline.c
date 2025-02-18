/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:19:09 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/18 19:57:32 by lemarino         ###   ########.fr       */
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

//"line_length" non corrisponde alla lunghezza effettiva della finestra quindi:
//offset = (y * line_length + x * (bits_per_pixel / 8));
static void	my_pixelput(t_myimg *img, double x, double y, int color)
{
	char	*dst;

	x += (img->line_length / 10);//##Sposta immagine verso il centro##
	y += 350;//##Sposta immagine verso il centro##
	if (x < 0 || x >= 1600 || y < 0 || y >= 900)
		return;
	dst = img->addr + ((int)y * img->line_length + (int)x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// Distances the points from each other.
static void	zooming(t_myimg *img, double *x0, double *y0, double *x1, double *y1)
{
	*x0 *= img->zoom;
	*y0 *= img->zoom;
	*x1 *= img->zoom;
	*y1 *= img->zoom;
}

//Applies isometric pojection.
void	ft_isometry(double *x, double *y, double z)
{
	double	prev_x = *x;//double?
	double	prev_y = *y;
	
	*x = (prev_x - prev_y) * cos(0.523599); //30^*(pi/180) == 0.523599 rad
	*y = (prev_x + prev_y) * sin(0.523599) - z;
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
	zooming(img, &x0, &y0, &x1, &y1);
	math.dx = fabs(x1 - x0);
	math.dy = fabs(y1 - y0);
	math.err = math.dx - math.dy;
	ft_setdirection(&math, x0, y0, x1, y1);
	if (math.dir_x > 0 && math.dir_y > 0)//nord-ovest
		while (x0 < x1 && y0 < y1)
		{
			my_pixelput(img, x0, y0, color);
			if (2 * math.err > -math.dy)
			{
				math.err -= math.dy;
				x0 += math.dir_x;
			}
			if (2 * math.err < math.dx)
			{
				math.err += math.dx;
				y0 += math.dir_y;
			}
		}
	if (math.dir_x > 0 && math.dir_y < 0)//nord-est
		while (x0 < x1 && y0 > y1)
		{
			my_pixelput(img, x0, y0, color);
			if (2 * math.err > -math.dy)
			{
				math.err -= math.dy;
				x0 += math.dir_x;
			}
			if (2 * math.err < math.dx)
			{
				math.err += math.dx;
				y0 += math.dir_y;
			}
		}
	if (math.dir_x < 0 && math.dir_y > 0)//sud-ovest
		while (x0 > x1 && y0 < y1)
		{
			my_pixelput(img, x0, y0, color);
			if (2 * math.err > -math.dy)
			{
				math.err -= math.dy;
				x0 += math.dir_x;
			}
			if (2 * math.err < math.dx)
			{
				math.err += math.dx;
				y0 += math.dir_y;
			}
		}
	if (math.dir_x < 0 && math.dir_y < 0)//sud-est
		while (x0 > x1 && y0 > y1)
		{
			my_pixelput(img, x0, y0, color);
			if (2 * math.err > -math.dy)
			{
				math.err -= math.dy;
				x0 += math.dir_x;
			}
			if (2 * math.err < math.dx)
			{
				math.err += math.dx;
				y0 += math.dir_y;
			}
		}
	my_pixelput(img, x1, y1, color);
}

void	draw(t_myimg *img)
{
	double	x;
	double	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (x < img->width - 1)
				ft_bresenham(img, x, y, x + 1, y, rgb_to_int(63, 210, 66));
			if (y < img->height - 1)
				ft_bresenham(img, x, y, x, y + 1, rgb_to_int(63, 210, 66));
			x++;
		}
		y++;
	}
}
