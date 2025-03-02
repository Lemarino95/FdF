/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotateaxis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:35:54 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/02 12:21:20 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_horizontal(int keysym, t_myimg *img)
{
	if (keysym == XK_d)
		img->angle_x += 0.01;
	if (keysym == XK_a)
		img->angle_x -= 0.01;
	if (img->angle_x > 2 * M_PI)
		img->angle_x -= 2 * M_PI;
	if (img->angle_x < -2 * M_PI)
		img->angle_x += 2 * M_PI;
	ft_backtoblack(img);
	draw(img);
	mlx_do_sync(img->mlx_ptr);
	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
}

static void	rotate_vertical(int keysym, t_myimg *img)
{
	if (keysym == XK_w)
		img->angle_y += 0.01;
	if (keysym == XK_s)
		img->angle_y -= 0.01;
	if (img->angle_y > 2 * M_PI)
		img->angle_y -= 2 * M_PI;
	if (img->angle_y < -2 * M_PI)
		img->angle_y += 2 * M_PI;
	ft_backtoblack(img);
	draw(img);
	mlx_do_sync(img->mlx_ptr);
	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
}

static void	rotate_plane(int keysym, t_myimg *img)
{
	if (keysym == XK_e)
		img->angle_z += 0.01;
	if (keysym == XK_q)
		img->angle_z -= 0.01;
	if (img->angle_z > 2 * M_PI)
		img->angle_z -= 2 * M_PI;
	if (img->angle_z < -2 * M_PI)
		img->angle_z += 2 * M_PI;
	ft_backtoblack(img);
	draw(img);
	mlx_do_sync(img->mlx_ptr);
	mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
}

void	rotate_axis(int keysym, t_myimg *img)
{
	if (keysym == XK_d || keysym == XK_a)
		rotate_horizontal(keysym, img);
	else if (keysym == XK_w || keysym == XK_s)
		rotate_vertical(keysym, img);
	else if (keysym == XK_e || keysym == XK_q)
		rotate_plane(keysym, img);
}
