/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:17:42 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/17 12:30:09 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


 
int	main(int ac, char **av)
{
	t_win	win;
	t_myimg	img;

	if (ac != 2)
		perror("ERR: too few arguments.");
	win.mlx_ptr = mlx_init();//leak
	if (win.mlx_ptr == NULL)
		return (0);
	win.mlx_win = mlx_new_window(win.mlx_ptr, 1600, 900, "FdF");//leak
	if (win.mlx_win == NULL)
		return (0);
	img.nimg = mlx_new_image(win.mlx_ptr, 1600, 900);//leak
	img.addr = mlx_get_data_addr(img.nimg, &img.bits_per_pixel,\
					&img.line_length, &img.endian);
	// ft_bresenham(&img, 200, 100, 300, 500, rgb_to_int(63, 210, 66));
	img.map = cartography(av[1]);
	img.zoom = 20;
	img.height = get_height(av[1]);
	img.width = get_width(av[1]);
	draw(&img);
	mlx_put_image_to_window(win.mlx_ptr, win.mlx_win, img.nimg, 0, 0);
	mlx_loop(win.mlx_ptr);
}
