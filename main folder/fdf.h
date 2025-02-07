/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:15 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/05 18:47:21 by lemarino         ###   ########.fr       */
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
	int			width;
	int			height;
}	t_win;

//

#endif
// cc starting.c -o my_program fdf.a minilibx-linux/libmlx.a -lm -lX11 -lXext