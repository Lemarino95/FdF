/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:58:44 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/24 21:23:33 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//"line_length" non corrisponde alla lunghezza effettiva della finestra quindi:
//offset = (y * line_length + x * (bits_per_pixel / 8));
static void	my_pixelput(t_myimg *img, double x, double y, int color)
{
	char	*dst;

	x += (WIN_LEN / 2);
	y += (WIN_HEIGHT / 2);
	if (x < 0 || x >= WIN_LEN || y < 0 || y >= WIN_HEIGHT)
		return;
	dst = img->addr + ((int)y * img->line_length + (int)x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	to_northwest(double x0, double x1, double y0, double y1, t_myimg img,\
						t_math *math, int color)
{
	while (x0 < x1 && y0 < y1)
		{
			my_pixelput(&img, x0, y0, color);
			if (2 * math->err > -math->dy)
			{
				math->err -= math->dy;
				x0 += math->dir_x;
			}
			if (2 * math->err < math->dx)
			{
				math->err += math->dx;
				y0 += math->dir_y;
			}
		}
}

void	to_northeast(double x0, double x1, double y0, double y1, t_myimg img,\
	t_math *math, int color)
{
	while (x0 < x1 && y0 > y1)
	{
		my_pixelput(&img, x0, y0, color);
		if (2 * math->err > -math->dy)
		{
			math->err -= math->dy;
			x0 += math->dir_x;
		}
		if (2 * math->err < math->dx)
		{
			math->err += math->dx;
			y0 += math->dir_y;
		}
	}
}

void	to_southwest(double x0, double x1, double y0, double y1, t_myimg img,\
	t_math *math, int color)
{
	while (x0 > x1 && y0 < y1)
	{
		my_pixelput(&img, x0, y0, color);
		if (2 * math->err > -math->dy)
		{
			math->err -= math->dy;
			x0 += math->dir_x;
		}
		if (2 * math->err < math->dx)
		{
			math->err += math->dx;
			y0 += math->dir_y;
		}
	}
}

void	to_southeast(double x0, double x1, double y0, double y1, t_myimg img,\
	t_math *math, int color)
{
	while (x0 > x1 && y0 > y1)
	{
		my_pixelput(&img, x0, y0, color);
		if (2 * math->err > -math->dy)
		{
			math->err -= math->dy;
			x0 += math->dir_x;
		}
		if (2 * math->err < math->dx)
		{
			math->err += math->dx;
			y0 += math->dir_y;
		}
	}
}
