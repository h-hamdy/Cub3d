# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>
# include "Cub3d.h"

void	init_gv()
{
	g_v.title_size = 32;
	g_v.map_num_rows = 15;
	g_v.map_num_cols = 33;
	g_v.map_num_width = g_v.map_num_cols * g_v.title_size;
	g_v.map_num_height = g_v.map_num_rows * g_v.title_size;
}

int	check_direction (char c) {
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

char	get_direction(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->info->map[i])
	{
		j = 0;
		while (game->info->map[i][j])
		{
			if (game->info->map[i][j] == 'N' || game->info->map[i][j] == 'S' || game->info->map[i][j] == 'W'
				|| game->info->map[i][j] == 'E') {
					game->info->map[i][j] = '0';
					game->p.row = i;
					game->p.col = j;
					game->p.x = game->p.col * g_v.title_size + g_v.title_size / 2;
					game->p.y = game->p.row * g_v.title_size + g_v.title_size / 2;
					return (game->info->map[i][j]);
				}
				j++;
		}
		i++;
	}
	return (0);
}

void	PlayerSetup(t_data *game) {
	char direction;

	direction = get_direction(game);
	if (direction == 'N')
		game->p.direction = 3 * (M_PI / 2);
	else if (direction == 'S')
		game->p.direction = M_PI / 2;
	else if (direction == 'E')
		game->p.direction = 0;
	else
		game->p.direction = M_PI; 
	game->p.moveSpeed = 5.0;
	game->p.rotationSpeed = 5 * (M_PI / 180);
}

void	my_mlx_pixel_put(t_data *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img.addr + (y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	rect(t_data *game, int i, int j, int len, int color)
{
	for (int l = 0; l < len; l++) {
		for (int k = 0; k < len; k++) {
			my_mlx_pixel_put(game, j + k, i + l, color);
		}
	}
}

void render_player (t_data *game) {
	int k = 0;

	rect(game, game->p.y - 3 , game->p.x - 3, 7, 0xff0000);
	while (k < 30) {
		my_mlx_pixel_put(
			game,
			game->p.x + cos(game->p.direction) * k,
			game->p.y + sin(game->p.direction) * k,
			0xff0000);
		k++;
	}
}

void	render_img (t_data *game) {
	int i = 0;
	int j;

	while (game->info->map[i]) {
		j = 0;
		while (game->info->map[i][j]) {
			if (game->info->map[i][j] == '0' || (i == game->p.row && j == game->p.col)) {
				rect(game, i * g_v.title_size, j * g_v.title_size, g_v.title_size, 0xD3D1D1);
			}
			else if (game->info->map[i][j] == '1')
				rect (game, i * g_v.title_size, j * g_v.title_size, g_v.title_size, 0x484747);
			j++;
		}
		i++;
	}
}

bool	isWall (t_data *game, double x, double y) {
	if (x < 0 || x > g_v.map_num_width || y < 0 || y > g_v.map_num_height)
		return (true);
	int x_index = x / g_v.title_size;
	int y_index = y / g_v.title_size;
	if (game->info->map[y_index][x_index] != '1') {
		game->p.x = x;
		game->p.y = y;
		return (false);
	}
	return (false);
}

int		key_pressed (int key, t_data *game) {
	double newx, newy = {0};

	if (key == EXIT)
		exit (1);
	if (key == TURN_LEFT)
		game->p.direction += -1 * game->p.rotationSpeed;
	else if (key == TURN_RIGHT)
		game->p.direction += 1 * game->p.rotationSpeed;
	else if (key == UP) {
		newx = game->p.x + cos(game->p.direction) * game->p.moveSpeed;
		newy = game->p.y + sin(game->p.direction) * game->p.moveSpeed;
	}
	else if (key == DOWN) {
		newx = game->p.x - cos(game->p.direction) * game->p.moveSpeed;
		newy = game->p.y - sin(game->p.direction) * game->p.moveSpeed;
	}
	else if (key == RIGHT) {
		newx = game->p.x + cos(game->p.direction + M_PI / 2) * game->p.moveSpeed;
		newy = game->p.y + sin(game->p.direction + M_PI / 2) * game->p.moveSpeed;
	}
	else if (key == LEFT) {
		newx = game->p.x - cos(game->p.direction + M_PI / 2) * game->p.moveSpeed;
		newy = game->p.y - sin(game->p.direction + M_PI / 2) * game->p.moveSpeed;
	}
	if (key == TURN_LEFT || key == TURN_RIGHT || ((key == UP || key == DOWN || key == RIGHT || key == LEFT) && (!isWall(game, newx, game->p.y)) && !isWall(game, game->p.x, newy))) {
		render_img(game);
		render_player(game);
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win, game->img.img, 0, 0);
	}
	return (0);
}


int main(int ac, char **av) {
	t_data game;

	init_gv();
	game.info = parsing (ac, av);
	game.mlx.mlx = mlx_init();
	game.mlx.mlx_win = mlx_new_window(game.mlx.mlx, 1054,  448, "Cub3d");
	game.img.img = mlx_new_image(game.mlx.mlx, 1054, 448);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
								&game.img.endian);
	PlayerSetup(&game);
	render_img(&game);
	render_player(&game);
	mlx_put_image_to_window(game.mlx.mlx, game.mlx.mlx_win, game.img.img, 0, 0);
	mlx_hook (game.mlx.mlx_win, 2, 0, key_pressed, &game);
	mlx_loop(game.mlx.mlx);
}