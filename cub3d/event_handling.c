# include "Cub3d.h"

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
	if (game->p.direction < 0)
		game->p.direction += M_PI * 2;
	else if (game->p.direction > M_PI * 2)
		game->p.direction -= M_PI * 2;
	if (key == TURN_LEFT || key == TURN_RIGHT || ((key == UP || key == DOWN || key == RIGHT || key == LEFT) && isWall(game, newx, game->p.y, 'y') == 0 && isWall(game, game->p.x, newy, 'y') == 0)) {
		render_img(game);
		render_player(game);
		raycasting(game);
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win, game->img.img, 0, 0);
	}
	return (0);
} 