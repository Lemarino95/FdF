/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:10:21 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/07 19:15:38 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//determina il colore del pixel
int rgb_to_int(double r, double g, double b)// double: high-precision floating-point data or numbers (up to 15 to 17 digits)
{
    int color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    return (color);
}

//Digital Differential Analyzer algorithm
void	ft_dda(void *mlx_ptr, void *mlx_win, int x1, int x2, int y1, int y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	int steps;
	int i = 0;
	if (fabsf(dx) > fabsf(dy))
		steps = dx;
	else
		steps = dy;
	while (i++ <= steps)
	{
		mlx_pixel_put(mlx_ptr, mlx_win, x1, y1, rgb_to_int(86, 169, 266));
		x1 += (dx)/steps;
		y1 += dy/steps;// 200/300 e' decimale. Devo lavorare con i resti delle divisioni.
	}
}


int	main()
{
	t_win win;
	int x = 400;
	int y = 200;

	win.mlx_ptr = mlx_init();
	if (win.mlx_ptr == NULL)
		return (0);

	win.mlx_win = mlx_new_window(win.mlx_ptr, 1000, 600, "fdf");
	if (win.mlx_win == NULL)
		return (0);

	/* while (x < 700 && y < 100)
	{
		mlx_pixel_put(win.mlx_ptr, win.mlx_win, x, y, 0xFFFFFF);
		x++;
		y++;
	} */
	/* while (1)
	{
		// mlx_pixel_put(win.mlx_ptr, win.mlx_win, x, y, 0x89351F);
		mlx_pixel_put(win.mlx_ptr, win.mlx_win, x, y, rgb_to_int(86, 169, 266));//mlx non daa' sempre colori opachi
		if (x < 700)
			x++;
		if (y < 400)
			y++;
		if (x >= 700 && y >= 400)
			break;
	} */

	ft_dda(win.mlx_ptr, win.mlx_win, x, 700, y, 400);

	mlx_loop(win.mlx_ptr);
	return (0);
}

/* vorrei usare l'algoritmo DDA per tracciare le linee sulla finestra. 
Dal momento che non posso usare i float, mi conviene lavorare intorno al modulo delle divisioni(%)? */