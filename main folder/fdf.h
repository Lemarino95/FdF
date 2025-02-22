/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:15 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/22 19:52:40 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H


# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
# include <X11/keysym.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MACROS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~VARs~~~~~~~~~~~~~~~*/
#define WIN_LEN 1600
#define WIN_HEIGHT 900

/*~~~~~~~~~~~~~~~COLORS~~~~~~~~~~~~~~~*/
#define NO_COLOR "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[36m"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct s_myimg
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*nimg;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			zoom;
	int			**map;
	int			height;
	int			width;
}	t_myimg;

// Used while reading the map from the .fdf file
typedef struct s_read
{
	char	**splitted_line;
	char	*line;
	char	*line2;
	int		fd;
}	t_read;

// Variables used for calculations in the pixelputting algorithm.
typedef struct s_math
{
	int	dx;
	int	dy;
	int	err;
	int	dir_x;
	int	dir_y;
}	t_math;

// void	ft_setdirection(int *dir_x, int *dir_y, int x0, int y0, int x1, int y1);
//void	my_pixelput(t_myimg *img, int x, int y, int color);
// void	ft_isometry(int *x, int *y, int z);
int		rgb_to_int(double r, double g, double b);
int		**cartography(char *map_file);
int		count_words(const char *str, char c);
int		get_height(char *map_file);
int		get_width(char *map_file);
void	draw(t_myimg *img);
void	ft_bresenham(t_myimg *img, double x0, double y0, double x1, double y1,\
							int color);
void	to_northwest(double x0, double x1, double y0, double y1, t_myimg img,\
							t_math *math, int color);
void	to_northeast(double x0, double x1, double y0, double y1, t_myimg img,\
							t_math *math, int color);
void	to_southwest(double x0, double x1, double y0, double y1, t_myimg img,\
							t_math *math, int color);
void	to_southeast(double x0, double x1, double y0, double y1, t_myimg img,\
							t_math *math, int color);
void	handle_input(t_myimg *img);
int		close_all(t_myimg *img);
void	ft_backtoblack(t_myimg *img);

#endif

// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

// /usr/include/X11/keysymdef.h
