/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stpiegazioneRick.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:10:21 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/06 17:28:21 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct info{
	void	*mlx;
	void	*window;

} t_info;

int handle_user_input(int button, void *arg){
	
	t_info *info = (t_info *)arg;
	if(button == 100)
	{
		//do something
	}
	
}

int game_loop(void *arg){
	t_info *info = (t_info *)arg;
	

	//algoritmo


//devi fare i calcoli con l algo per capire ogni pixel dello schermo di che colore e'
//devi attraversare lo schermo/matrice
//per ogni pixel dello schermo l algo ti dice il colore(int)
//devi trovare il corrispettivo della poszione delle schermo/matrice nel FRAME (sdati[y * lenRiga + x])
//devi scomporre l int in 4 char usando shift binari perche ogni pixel e' rappr. da 4 char (RGBA) 
//spingerlo  dentro il char * ovvero il FRAME
//mettere il FRAME a schermo
	
schermo:
int 11111111 11111111 11111111 11111111
[......xxxxxxxxxxxx..
..................x..
X......X............]

xo = 2
yo = 5
[........................
....o...................
........................]

sdati[y * lenRiga + y]// trova la posizione del pixel nella finestra
//cambiare colore del pixel
4 operazioni 
sdati[y * lenRiga + x] + 0 = x << 0
sdati[y * lenRiga + x] + 1 = 11111111 00000000 00000000 00000000 << 1 // shiftando diventa "00000000 00000000 00000000 00000000"
sdati[y * lenRiga + x] + 2 = 11111111 00000000 00000000 00000000 << 3
sdati[y * lenRiga + x] + 3 = 11111111 00000000 00000000 00000000 << 4 

255 0  0 0



unsigned char 0-255
sdati   char* [255, 0, 0, 0, ........................................................................]



	//print to window
}

int	main()
{
	t_info info;

	info = (t_info){0};
	info.mlx = mlx_init();
	if (!info.mlx)
		return (1);
	info.window = mlx_new_window(info.mlx, 800, 600, "FdF");

	
	mlx_hook(info.window,  KeyPress, KeyPressMask, handle_user_input ,&info);//prende l'imput da periferica

	
	mlx_loop_hook(info.mlx, game_loop, &info);//

	mlx_loop(info.mlx);
}

/* int	main()
{
	t_win win;

	win.mlx_ptr = mlx_init();
	if (win.mlx_ptr == NULL)
		return (0);
	win.mlx_win = mlx_new_window(win.mlx_ptr, 1000,
			600, "fdf");
	if (win.mlx_win == NULL)
		return (0);
	mlx_loop(win.mlx_ptr);
	return (0);
} */
