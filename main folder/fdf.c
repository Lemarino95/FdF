/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:17:42 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/11 16:57:40 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//determina il colore del pixel.
int rgb_to_int(double r, double g, double b)// double: high-precision floating-point img or numbers (up to 15 to 17 digits)
{
    int color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    return (color);
}

//applica la proiezione isometrica.
void	ft_isometry(int *x, int *y, int z)
{
	int	prev_x = *x;
	int	prev_y = *y;
	
	*x = (prev_x - prev_y) * cos(0.523599); //30^*(pi/180) == 0.523599 rad
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

//"line_length" non corrisponde alla lunghezza effettiva della finestra quindi:
//offset = (y * line_length + x * (bits_per_pixel / 8));
void	my_pixelput(t_myimg *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// Algoritmo per il tracciamento della linea da x0y0 a x1y1.
void    ft_bresenham(t_myimg *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;
    
    while (1)
    {
        my_pixelput(img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

int	main()
{
	t_win	win;
	t_myimg	img;

	win.mlx_ptr = mlx_init();//leak
	if (win.mlx_ptr == NULL)
		return (0);
	win.mlx_win = mlx_new_window(win.mlx_ptr, 800, 600, "FdF");//leak
	if (win.mlx_win == NULL)
		return (0);
	img.nimg = mlx_new_image(win.mlx_ptr, 800, 600);//leak
	img.addr = mlx_get_data_addr(img.nimg, &img.bits_per_pixel,\
					&img.line_length, &img.endian);
	ft_bresenham(&img, 400, 200, 700, 300, rgb_to_int(63, 210, 66));
	my_pixelput(&img, 700, 300, rgb_to_int(174, 59, 200));
	mlx_put_image_to_window(win.mlx_ptr, win.mlx_win, img.nimg, 0, 0);
	
	mlx_loop(win.mlx_ptr);
}
