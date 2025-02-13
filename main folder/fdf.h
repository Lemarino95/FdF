/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:15 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/13 20:58:55 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H


# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>

typedef struct s_win
{
	void		*mlx_ptr;
	void		*mlx_win;
}	t_win;

typedef struct s_myimg
{
	void		*nimg;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_myimg;

typedef struct s_read
{
	char	**splitted_line;
	char	*line;
	int		fd;
}	t_read;

void	ft_bresenham(t_myimg *img, int x0, int y0, int x1, int y1, int color);
void	ft_setdirection(int *dir_x, int *dir_y, int x0, int y0, int x1, int y1);
void	my_pixelput(t_myimg *img, int x, int y, int color);
void	ft_isometry(int *x, int *y, int z);
int		rgb_to_int(double r, double g, double b);
int	**cartography(char *map_file);

#endif

// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all
