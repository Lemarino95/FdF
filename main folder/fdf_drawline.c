/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:58:44 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/26 20:50:52 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//"line_length" non corrisponde alla lunghezza effettiva della finestra quindi:
//offset = (y * line_length + x * (bits_per_pixel / 8));
static void	my_pixelput(t_myimg *img, double x, double y, int color)
{
	char	*dst;

	x += (WIN_LEN / 2) + img->t_x;
	y += (WIN_HEIGHT / 2) + img->t_y;
	if (x < 0 || x >= WIN_LEN || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + ((int)y * img->line_length + (int)x * \
										(img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	to_northwest(t_myimg img, t_math *math, int color)
{
	while (math->x < math->x1 && math->y < math->y1)
	{
		my_pixelput(&img, math->x, math->y, color);
		if (2 * math->err > -math->dy)
		{
			math->err -= math->dy;
			math->x += math->dir_x;
		}
		if (2 * math->err < math->dx)
		{
			math->err += math->dx;
			math->y += math->dir_y;
		}
	}
}

void	to_northeast(t_myimg img, t_math *math, int color)
{
	while (math->x < math->x1 && math->y > math->y1)
	{
		my_pixelput(&img, math->x, math->y, color);
		if (2 * math->err > -math->dy)
		{
			math->err -= math->dy;
			math->x += math->dir_x;
		}
		if (2 * math->err < math->dx)
		{
			math->err += math->dx;
			math->y += math->dir_y;
		}
	}
}

void	to_southwest(t_myimg img, t_math *math, int color)
{
	while (math->x > math->x1 && math->y < math->y1)
	{
		my_pixelput(&img, math->x, math->y, color);
		if (2 * math->err > -math->dy)
		{
			math->err -= math->dy;
			math->x += math->dir_x;
		}
		if (2 * math->err < math->dx)
		{
			math->err += math->dx;
			math->y += math->dir_y;
		}
	}
}

void	to_southeast(t_myimg img, t_math *math, int color)
{
	while (math->x > math->x1 && math->y > math->y1)
	{
		my_pixelput(&img, math->x, math->y, color);
		if (2 * math->err > -math->dy)
		{
			math->err -= math->dy;
			math->x += math->dir_x;
		}
		if (2 * math->err < math->dx)
		{
			math->err += math->dx;
			math->y += math->dir_y;
		}
	}
}
