# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>

struct Player {
	double x;
	double y;
	int row;
	int col;
	double direction;
	float moveSpeed;
	double rotationSpeed;
};

struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct 	my_mlx {
	void	*mlx;
	void	*mlx_win;
};

typedef	struct 
{
	struct Player p;
	struct s_data img;
	struct my_mlx mlx;
}			data;

const	int	TITLE_SIZE = 60;
const	int	MAP_NUM_ROWS = 12;
const	int	MAP_NUM_COLS = 15;
const	int	MAP_NUM_WIDTH = MAP_NUM_COLS * TITLE_SIZE;
const	int	MAP_NUM_HEIGHT = MAP_NUM_ROWS * TITLE_SIZE;


char str[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', 'N', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'}, 
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '1', '1', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

int	check_direction (char c) {
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

void	PlayerSetup(data *game) {
	char direction;
	for (int i = 0; i < MAP_NUM_ROWS; i++) {
		for (int j = 0; j < MAP_NUM_COLS; j++)
			if (check_direction(str[i][j])) {
				direction = str[i][j];
				str[i][j] = 0;
				game->p.row = i;
				game->p.col = j;
				game->p.x = game->p.col * TITLE_SIZE + TITLE_SIZE / 2;
				game->p.y = game->p.row * TITLE_SIZE + TITLE_SIZE / 2;
			}
	}
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

void	my_mlx_pixel_put(data *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img.addr + (y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	rect(data *game, int i, int j, int len, int color)
{
	for (int l = 0; l < len; l++) {
		for (int k = 0; k < len; k++) {
			my_mlx_pixel_put(game, j + k, i + l, color);
		}
	}
}

void render_player (data *game) {
	int k = 0;

	rect(game, game->p.y - 3 , game->p.x - 3, 7, 0xff0000);
	while (k < 60) {
		my_mlx_pixel_put(
			game,
			game->p.x + cos(game->p.direction) * k,
			game->p.y + sin(game->p.direction) * k,
			0xff0000);
		k++;
	}
}

void	render_img (data *game) {
	int i = 0;
	int j = 0;

	while (i < MAP_NUM_ROWS) {
		j = 0;
		while (j < MAP_NUM_COLS) {
			if (str[i][j] == '0' || (i == game->p.row && j == game->p.col)) {
				rect(game, i * TITLE_SIZE, j * TITLE_SIZE, TITLE_SIZE - 1, 0xD3D1D1);
			}
			else if (str[i][j] == '1')
				rect (game, i * TITLE_SIZE, j * TITLE_SIZE, TITLE_SIZE - 1, 0x484747);
			j++;
		}
		i++;
	}
}

bool	isWall (data *game, double x, double y) {
	if (x < 0 || x > MAP_NUM_WIDTH || y < 0 || y > MAP_NUM_HEIGHT)
		return (true);
	int x_index = x / TITLE_SIZE;
	int y_index = y / TITLE_SIZE;
	if (str[y_index][x_index] != '1') {
		game->p.x = x;
		game->p.y = y;
		return (false);
	}
	return (false);
}

int		key_pressed (int key, data *game) {
	double newx, newy = {0};

	if (key == 53)
		exit (1);
	if (key == 123)
		game->p.direction += -1 * game->p.rotationSpeed;
	else if (key == 124)
		game->p.direction += 1 * game->p.rotationSpeed;
	else if (key == 13) {
		newx = game->p.x + cos(game->p.direction) * game->p.moveSpeed;
		newy = game->p.y + sin(game->p.direction) * game->p.moveSpeed;
	}
	else if (key == 1) {
		newx = game->p.x - cos(game->p.direction) * game->p.moveSpeed;
		newy = game->p.y - sin(game->p.direction) * game->p.moveSpeed;
	}
	else if (key == 2) {
		newx = game->p.x + cos(game->p.direction + M_PI / 2) * game->p.moveSpeed;
		newy = game->p.y + sin(game->p.direction + M_PI / 2) * game->p.moveSpeed;
	}
	else if (key == 0) {
		newx = game->p.x - cos(game->p.direction + M_PI / 2) * game->p.moveSpeed;
		newy = game->p.y - sin(game->p.direction + M_PI / 2) * game->p.moveSpeed;
	}
	if (key == 123 || key == 124 || ((key == 13 || key == 1 || key == 2 || key == 0) && (!isWall(game, newx, game->p.y)) && !isWall(game, game->p.x, newy))) {
		render_img(game);
		render_player(game);
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win, game->img.img, 0, 0);
	}
	return (0);
}

int main(void){
	data	game;

	game.mlx.mlx = mlx_init();
	game.mlx.mlx_win = mlx_new_window(game.mlx.mlx, MAP_NUM_WIDTH,  MAP_NUM_HEIGHT, "Cub3d");
	game.img.img = mlx_new_image(game.mlx.mlx, MAP_NUM_WIDTH, MAP_NUM_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
								&game.img.endian);
	PlayerSetup(&game);
	render_img(&game);
	render_player(&game);
	mlx_put_image_to_window(game.mlx.mlx, game.mlx.mlx_win, game.img.img, 0, 0);
	mlx_hook (game.mlx.mlx_win, 2, 0, key_pressed, &game);
	mlx_loop(game.mlx.mlx);
}