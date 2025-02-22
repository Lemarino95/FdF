/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:17:42 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/22 20:05:56 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
 
int	main(int ac, char **av)
{
	t_myimg	img;

	if (ac != 2)
	{
		perror("ERR: invalid number of arguments.");
		exit(0);
	}
	img.mlx_ptr = mlx_init();
	if (img.mlx_ptr == NULL)
		return (0);
	img.mlx_win = mlx_new_window(img.mlx_ptr, WIN_LEN, WIN_HEIGHT, "FdF");
	if (img.mlx_win == NULL)
	return (0);
	img.nimg = mlx_new_image(img.mlx_ptr, WIN_LEN, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.nimg, &img.bits_per_pixel,\
		&img.line_length, &img.endian);
	img.zoom = 20;//##########ZooM#############
	handle_input(&img);
	img.map = cartography(av[1]);
	img.height = get_height(av[1]);//errore con linee vuote
	img.width = get_width(av[1]);//errore con spazi alla fine della prima riga
	printf(YELLOW "Map size(h*w) = %dx%d\n" NO_COLOR, img.height, img.width);//######
	draw(&img);
	mlx_put_image_to_window(img.mlx_ptr, img.mlx_win, img.nimg, 0, 0);
	mlx_loop(img.mlx_ptr);
}
