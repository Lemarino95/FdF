/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:15 by lemarino          #+#    #+#             */
/*   Updated: 2025/03/06 12:54:33 by lemarino         ###   ########.fr       */
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
	float		angle_x;//   Rotation modifier
	float		angle_y;//   Rotation modifier
	float		angle_z;//   Rotation modifier
}	t_myimg;

// Used while reading the map from the .fdf file
typedef struct s_read
{
	int		fd;
	char	*line;// Line read from file
	char	*line2;// Line without '\n'
	char	**splitted_line;// Array of single words taken from *line2
}	t_read;

// Variables used for calculations in the pixelputting algorithm.
typedef struct s_math
{
	int		i;
	int		j;
	float	x;
	float	x1;
	float	y;
	float	y1;
	float	z;
	float	z1;
	int		dx;
	int		dy;
	int		err;
	int		dir_x;
	int		dir_y;
}	t_math;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int		**cartography(char *map_file, int select, t_myimg *img);
int		**z_mtrx_creator(t_read *mapper, int **map, t_myimg *img);
int		**col_mtrx_creator(t_read *mapper, int **map, t_myimg *img);
int		get_height(char *map_file);
int		get_width(char *map_file);
void	define_vars(t_myimg *img);
void	draw(t_myimg *img);
void	ft_backtoblack(t_myimg *img);
void	rotate_coords(t_myimg *img, t_math *math);
void	ft_setscale(t_myimg *img, t_math *math);
void	to_northwest(t_myimg img, t_math *math, int color);
void	to_northeast(t_myimg img, t_math *math, int color);
void	to_southwest(t_myimg img, t_math *math, int color);
void	to_southeast(t_myimg img, t_math *math, int color);
void	handle_input(t_myimg *img);
void	rotate_axis(int keysym, t_myimg *img);
void	set_topview(t_myimg *img);
void	put_message(t_myimg *img);
void	permission_check(t_read *mapper, t_myimg *img);
int		arg_check(int ac, char **av);
void	sizes_check(t_myimg *img);
void	content_check(t_myimg *img);
char	**freesplit(char **s);
void	free_maputils(t_read *mapping);
int		free_maps(t_myimg *img);
int		close_all(t_myimg *img);

#endif

// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all 
