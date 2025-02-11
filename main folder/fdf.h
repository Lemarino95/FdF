/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:15 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/11 16:58:10 by lemarino         ###   ########.fr       */
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
	// int		width;
	// int		height;
}	t_win;

typedef struct s_myimg
{
	void		*nimg;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_myimg;

//

#endif

// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all
