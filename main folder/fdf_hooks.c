/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:19:55 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/01 14:25:45 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zooming(int keysym, t_myimg *img)
{
	if (keysym == XK_r)
	{
		img->zoom += 1;
		ft_backtoblack(img);
		draw(img);
		mlx_do_sync(img->mlx_ptr); // Dovrebbe ridurre il fluttering
		mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
	}
	else if (keysym == XK_f && img->zoom > 2)
	{
		img->zoom -= 1;
		ft_backtoblack(img);
		draw(img);
		mlx_do_sync(img->mlx_ptr);
		mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
	}
}

static void	traslate_y(int keysym, t_myimg *img)
{
	if (keysym == XK_Down)
	{
		img->t_y += 5;
		ft_backtoblack(img);
		draw(img);
		mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
	}
	if (keysym == XK_Up)
	{
		img->t_y -= 5;
		ft_backtoblack(img);
		draw(img);
		mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
	}
}

static void	traslate_x(int keysym, t_myimg *img)
{
	if (keysym == XK_Right)
	{
		img->t_x += 5;
		ft_backtoblack(img);
		draw(img);
		mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
	}
	if (keysym == XK_Left)
	{
		img->t_x -= 5;
		ft_backtoblack(img);
		draw(img);
		mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
	}
}

static int	handle_key(int keysym, void *param)
{
	t_myimg	*img;

	img = (t_myimg *)param;
	if (keysym == XK_r || keysym == XK_f)
		zooming(keysym, img);
	else if (keysym == XK_Left || keysym == XK_Right)
		traslate_x(keysym, img);
	else if (keysym == XK_Up || keysym == XK_Down)
		traslate_y(keysym, img);
	else if (keysym == XK_d || keysym == XK_a || keysym == XK_w || \
					keysym == XK_s || keysym == XK_e || keysym == XK_q)
		rotate_axis(keysym, img);
	else if (keysym == XK_Escape || keysym == XK_Delete)
		close_all(img);
	return (0);
}

void	handle_input(t_myimg *img)
{
	mlx_hook(img->mlx_win, 17, 1L << 17, close_all, img);
	mlx_hook(img->mlx_win, 2, 1L << 0, handle_key, img);
}
