# include "Cub3d.h"

int main(int ac, char **av) {
	t_data game;
	// t_wall *wall;

	init_gv();
	game.info = parsing (ac, av);
	game.mlx.mlx = mlx_init();
	game.mlx.mlx_win = mlx_new_window(game.mlx.mlx, WINDOW_WIDTH,  WINDOW_HEIGHT, "Cub3d");
	game.img.img = mlx_new_image(game.mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img,
		&game.img.bits_per_pixel, &game.img.line_length,
		&game.img.endian);
	game_Setup(&game);
	// render_img(&game);
	// render_player(&game);
	game.wall = raycasting(&game);
	render_3d(&game);
	// mlx_put_image_to_window(game.mlx.mlx, game.mlx.mlx_win, game.img.img, 0, 0);
	mlx_hook (game.mlx.mlx_win, 2, 0, key_pressed, &game);
	mlx_loop(game.mlx.mlx);
}