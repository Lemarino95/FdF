/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:17:42 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/28 19:49:08 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
 
void	define_vars(t_myimg *img)
{
	t_math	math;

	img->zoom = 20;//##########ZooM#############
	img->t_x = 0;
	img->t_y = 0;
	math.angle_x = 0.523599;//modificare ft_isometry per passargli t_math
	math.angle_y = 0.523599;
	// math.angle_z = 
}

int	main(int ac, char **av)
{
	t_myimg	img;

	error_control(ac, av);
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
	img.map = cartography(av[1], 1);
	img.colmap = cartography(av[1], 2);
	img.height = get_height(av[1]);
	img.width = get_width(av[1]);
	printf(YELLOW "Map size(h*w) = %dx%d\n" NO_COLOR, img.height, img.width);//################
	draw(&img);
	mlx_put_image_to_window(img.mlx_ptr, img.mlx_win, img.nimg, 0, 0);
	mlx_loop(img.mlx_ptr);
}
