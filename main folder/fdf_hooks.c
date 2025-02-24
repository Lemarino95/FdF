/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:19:55 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/24 11:07:26 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int zooming(int keysym, t_myimg *img)
{
	if (keysym == XK_Up)
	{
		img->zoom += 1;
		ft_backtoblack(img);
		draw(img);
		// mlx_do_sync(img->mlx_ptr); // Dovrebbe ridurre il fluttering
		mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
	}
	else if (keysym == XK_Down)
		if (img->zoom > 2)
		{
			img->zoom -= 1;
			ft_backtoblack(img);
			draw(img);
			// mlx_do_sync(img->mlx_ptr);
			mlx_put_image_to_window(img->mlx_ptr, img->mlx_win, img->nimg, 0, 0);
		}
	return (0);
}
		
static int	handle_key(int keysym, void *param)
{
	t_myimg *img;

	img = (t_myimg *)param;
	if (keysym == XK_Escape || keysym == XK_Delete)
		close_all(img);
	else if (keysym == XK_Up || keysym == XK_Down)
		zooming(keysym, img);
	return (0);
}

void	handle_input(t_myimg *img)
{
	mlx_hook(img->mlx_win, 17, 1L << 17, close_all, img);//per X
	// mlx_key_hook(img->mlx_win, handle_key, img);//per tasti
	mlx_hook(img->mlx_win, 2, 1L << 0, handle_key, img);//per tasti
	// mlx_hook(img->mlx_win, 3, 1L << 1, handle_key, img);//per tasti, funziona quando rilascio il tasto.
}
