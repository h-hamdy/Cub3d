/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:11 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/19 16:38:26 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_textures(t_data *g)
{
	int	x;
	int	y;

	g->tex.ea = mlx_xpm_file_to_image(g->mlx.mlx, g->info->ea, &x, &y);
	g->tex.ea_addr = mlx_get_data_addr(g->tex.ea, \
	&g->tex.img.bits_per_pixel, &g->tex.img.line_length, &g->tex.img.endian);
	g->tex.we = mlx_xpm_file_to_image(g->mlx.mlx, g->info->we, &x, &y);
	g->tex.we_addr = mlx_get_data_addr(g->tex.we, \
	&g->tex.img.bits_per_pixel, &g->tex.img.line_length, &g->tex.img.endian);
	g->tex.so = mlx_xpm_file_to_image(g->mlx.mlx, g->info->so, &x, &y);
	g->tex.so_addr = mlx_get_data_addr(g->tex.so, \
	&g->tex.img.bits_per_pixel, &g->tex.img.line_length, &g->tex.img.endian);
	g->tex.no = mlx_xpm_file_to_image(g->mlx.mlx, g->info->no, &x, &y);
	g->tex.no_addr = mlx_get_data_addr(g->tex.no, \
	&g->tex.img.bits_per_pixel, &g->tex.img.line_length, &g->tex.img.endian);
}

int	main(int ac, char **av)
{
	t_data		game;

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
		init_textures(&game);
		game.wall = raycasting(&game);
		render_3d(&game);
		mlx_put_image_to_window(game.mlx.mlx, game.mlx.mlx_win, \
			game.img.img, 0, 0);
		mlx_hook (game.mlx.mlx_win, 2, 0, key_pressed, &game);
		mlx_loop(game.mlx.mlx);
	}
}
