/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:19:09 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/12 18:19:22 by lemarino         ###   ########.fr       */
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

//Applies isometric pojection.
void	ft_isometry(int *x, int *y, int z)
{
	int	prev_x = *x;
	int	prev_y = *y;
	
	*x = (prev_x - prev_y) * cos(0.523599); //30^*(pi/180) == 0.523599 rad
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

//"line_length" non corrisponde alla lunghezza effettiva della finestra quindi:
//offset = (y * line_length + x * (bits_per_pixel / 8));
void	my_pixelput(t_myimg *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// Determines in which direction the line is to be drawn.
void	ft_setdirection(int *dir_x, int *dir_y, int x0, int y0, int x1, int y1)
{
	*dir_x = 1;
	*dir_y = 1;
	if (x0 > x1)
		*dir_x = -1;
	if (y0 > y1)
		*dir_y = -1;
}

// Algorithm to trace a line from x0y0 to x1y1.
void    ft_bresenham(t_myimg *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	err;
	int	dir_x;
	int	dir_y;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
	ft_setdirection(&dir_x, &dir_y, x0, y0, x1, y1);
	while (x0 != x1 || y0 != y1)
	{
		my_pixelput(img, x0, y0, color);
		if (2 * err > -dy)
		{
			err -= dy;
			x0 += dir_x;
		}
		if (2 * err < dx)
		{
			err += dx;
			y0 += dir_y;
		}
	}
	my_pixelput(img, x1, y1, color);
}