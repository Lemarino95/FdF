/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:17:42 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/02 13:04:17 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
 
void	put_message(t_myimg *img)
{
	mlx_string_put(img->mlx_ptr, img->mlx_win, 25, 25, 0x9FFF9F, "Arrow keys: traslate");
	mlx_string_put(img->mlx_ptr, img->mlx_win, 25, 50, 0x9FFF9F, "r: Zoom in");
	mlx_string_put(img->mlx_ptr, img->mlx_win, 25, 75, 0x9FFF9F, "f: Zoom out");
	mlx_string_put(img->mlx_ptr, img->mlx_win, 25, 100, 0x9FFF9F, "a & d: Rotate on x axis");
	mlx_string_put(img->mlx_ptr, img->mlx_win, 25, 125, 0x9FFF9F, "w & s: Rotate on y axis");
	mlx_string_put(img->mlx_ptr, img->mlx_win, 25, 150, 0x9FFF9F, "q & e: Rotate on z axis");
	mlx_string_put(img->mlx_ptr, img->mlx_win, 25, 175, 0x9FFF9F, "Esc or Delete: Close session");
}

void	define_vars(t_myimg *img)
{
	img->zoom = 20;
	img->t_x = 0;
	img->t_y = 0;
	img->angle_x = 6;
	img->angle_y = 0.3;
	img->angle_z = 0.01;
}



int	main(int ac, char **av)
{
	t_myimg	img;

	arg_check(ac, av);
	img.mlx_ptr = mlx_init();
	if (img.mlx_ptr == NULL)
		return (0);
	img.mlx_win = mlx_new_window(img.mlx_ptr, WIN_LEN, WIN_HEIGHT, "FdF");
	if (img.mlx_win == NULL)
		return (0);
	img.nimg = mlx_new_image(img.mlx_ptr, WIN_LEN, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.nimg, &img.bits_per_pixel,\
		&img.line_length, &img.endian);
	define_vars(&img);
	handle_input(&img);
	img.map = cartography(av[1], 1, &img);
	img.colmap = cartography(av[1], 2, &img);
	img.height = get_height(av[1]);
	img.width = get_width(av[1]);
	draw(&img);
	mlx_put_image_to_window(img.mlx_ptr, img.mlx_win, img.nimg, 0, 0);
	put_message(&img);
	mlx_loop(img.mlx_ptr);
}
