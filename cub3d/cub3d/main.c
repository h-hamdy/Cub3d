/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:49:11 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/20 03:40:59 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_textures(t_data *g)
{
	int	x;
	int	y;

	g->tex.ea = mlx_xpm_file_to_image(g->mlx.mlx, g->info->ea, &x, &y);
	if (!g->tex.ea)
		print_error("Invalid path of textures\n");
	g->tex.ea_addr = mlx_get_data_addr(g->tex.ea, \
	&g->tex.img.bits_per_pixel, &g->tex.img.line_length, &g->tex.img.endian);
	g->tex.we = mlx_xpm_file_to_image(g->mlx.mlx, g->info->we, &x, &y);
	if (!g->tex.we)
		print_error("Invalid path of textures\n");
	g->tex.we_addr = mlx_get_data_addr(g->tex.we, \
	&g->tex.img.bits_per_pixel, &g->tex.img.line_length, &g->tex.img.endian);
	g->tex.so = mlx_xpm_file_to_image(g->mlx.mlx, g->info->so, &x, &y);
	if (!g->tex.so)
		print_error("Invalid path of textures\n");
	g->tex.so_addr = mlx_get_data_addr(g->tex.so, \
	&g->tex.img.bits_per_pixel, &g->tex.img.line_length, &g->tex.img.endian);
	g->tex.no = mlx_xpm_file_to_image(g->mlx.mlx, g->info->no, &x, &y);
	if (!g->tex.no)
		print_error("Invalid path of textures\n");
	g->tex.no_addr = mlx_get_data_addr(g->tex.no, \
	&g->tex.img.bits_per_pixel, &g->tex.img.line_length, &g->tex.img.endian);
	g->tex.c_rgb = rgb_to_hex(g->info->c[0], g->info->c[1], g->info->c[2]);
	g->tex.f_rgb = rgb_to_hex(g->info->f[0], g->info->f[1], g->info->f[2]);
}

void	render_mini_map(t_data *game)
{
	render_img(game);
	render_player(game, game->p.x - 5, game->p.y - 5, 0xff0000);
	render_line(game, 30, game->p.direction);
}

int	mouse_event_handler(int button, int x, int y, t_data *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		game->p.direction += -1 * game->p.rotation_speed;
	else if (button == 2)
		game->p.direction += 1 * game->p.rotation_speed;
	if (button == 1 || button == 2)
	{
		game->wall = raycasting(game);
		render_3d(game);
		render_mini_map(game);
		mlx_put_image_to_window(game->mlx.mlx, \
			game->mlx.mlx_win, game->img.img, 0, 0);
		normalize(game);
	}
	return (0);
}

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
		init_textures(&game);
		game.wall = raycasting(&game);
		render_3d(&game);
		render_mini_map(&game);
		mlx_put_image_to_window(game.mlx.mlx, game.mlx.mlx_win, \
			game.img.img, 0, 0);
		mlx_hook(game.mlx.mlx_win, 4, 0, mouse_event_handler, &game);
		mlx_hook (game.mlx.mlx_win, 2, 0, key_pressed, &game);
		mlx_loop(game.mlx.mlx);
	}
}
