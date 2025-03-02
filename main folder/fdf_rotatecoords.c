/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotatecoords.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:09:45 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/02 19:23:13 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Distances the points from each other.
void	ft_setscale(t_myimg *img, t_math *math)
{
	math->x *= img->zoom;
	math->y *= img->zoom;
	math->x1 *= img->zoom;
	math->y1 *= img->zoom;
}

// Rotation around the horizontal axys
static void	rotate_x(float *y, float *z, float *angle)
{
	float	prev_y;
	float	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(*angle) - prev_z * sin(*angle);
	*z = prev_y * sin(*angle) + prev_z * cos(*angle);
}

// Rotation around the vertical axys
static void	rotate_y(float *x, float *z, float *angle)
{
	float	prev_x;
	float	prev_z;

	prev_x = *x;
	prev_z = *z;
	*x = prev_x * cos(*angle) + prev_z * sin(*angle);
	*z = -prev_x * sin(*angle) + prev_z * cos(*angle);
}

static void	rotate_z(float *x, float *y, float *angle)
{
	float	prev_x;
	float	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(*angle) - prev_y * sin(*angle);
	*y = prev_x * sin(*angle) + prev_y * cos(*angle);
}

void	rotate_coords(t_myimg *img, t_math *math)
{
	float center_x = img->width / 2.0;
	float center_y = img->height / 2.0;

	math->x -= center_x;
	math->y -= center_y;
	math->x1 -= center_x;
	math->y1 -= center_y;
	rotate_x(&math->y, &math->z, &img->angle_x);
	rotate_y(&math->x, &math->z, &img->angle_y);
	rotate_z(&math->x, &math->y, &img->angle_z);
	rotate_x(&math->y1, &math->z1, &img->angle_x);
	rotate_y(&math->x1, &math->z1, &img->angle_y);
	rotate_z(&math->x1, &math->y1, &img->angle_z);
	math->x += center_x;
	math->y += center_y;
	math->x1 += center_x;
	math->y1 += center_y;
}
