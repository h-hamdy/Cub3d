/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:11 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/17 16:02:05 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	main(int ac, char **av)
{
	t_data	game;

	if (ac > 1)
	{
		init_gv();
		game.info = parsing (ac, av);
		game.mlx.mlx = mlx_init();
		game.mlx.mlx_win = mlx_new_window(game.mlx.mlx, WINDOW_WIDTH, \
			WINDOW_HEIGHT, "Cub3d");
		game.img.img = mlx_new_image(game.mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		game.img.addr = mlx_get_data_addr(game.img.img,
				&game.img.bits_per_pixel, &game.img.line_length,
				&game.img.endian);
		game_setup(&game);
		game.wall = raycasting(&game);
		render_3d(&game);
		mlx_put_image_to_window(game.mlx.mlx, game.mlx.mlx_win, game.img.img, 0, 0);
		mlx_hook (game.mlx.mlx_win, 2, 0, key_pressed, &game);
		mlx_loop(game.mlx.mlx);
	}
}
