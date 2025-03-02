/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:15 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/02 12:38:01 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MACROS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~VARs~~~~~~~~~~~~~~~~*/
# define WIN_LEN	1600
# define WIN_HEIGHT	900
# define M_PI		3.14159265358979323846

/*~~~~~~~~~~~~~~~COLORS~~~~~~~~~~~~~~~*/
# define NO_COLOR "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[36m"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~STRUCTS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct s_myimg
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*nimg;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			**map;
	int			**colmap;
	int			height;
	int			width;
	int			zoom;//         Scale modifier
	int			t_x;//     Traslation modifier
	int			t_y;//     Traslation modifier
	double		angle_x;//   Rotation modifier
	double		angle_y;//   Rotation modifier
	double		angle_z;//   Rotation modifier
	int			proj_flag;// Projection selector
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
	int		i;
	int		j;
	double	x;
	double	x1;
	double	y;
	double	y1;
	double	z;
	double	z1;
	int		dx;
	int		dy;
	int		err;
	int		dir_x;
	int		dir_y;
}	t_math;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int		**cartography(char *map_file, int select, t_myimg *img);
int		get_height(char *map_file);
int		get_width(char *map_file);
void	draw(t_myimg *img);
void	iso_bresenham(t_myimg *img, t_math *math, int color);
void	stereo_bresenham(t_myimg *img, t_math *math, int color);
void	to_northwest(t_myimg img, t_math *math, int color);
void	to_northeast(t_myimg img, t_math *math, int color);
void	to_southwest(t_myimg img, t_math *math, int color);
void	to_southeast(t_myimg img, t_math *math, int color);
void	handle_input(t_myimg *img);
int		close_all(t_myimg *img);
int		free_maps(t_myimg *img);
char	**freesplit(char **s);
void	ft_backtoblack(t_myimg *img);
int		arg_num_check(int ac, char **av);
void	permission_check(t_read *mapper, t_myimg *img);
void	rotate_coords(t_myimg *img, t_math *math);
void	ft_setscale(t_myimg *img, t_math *math);
void	rotate_axis(int keysym, t_myimg *img);
void	put_message(t_myimg *img);

#endif

// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all 
