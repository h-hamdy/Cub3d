# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include "Cub3d.h"

void	init_gv()
{
	g_v.title_size = 32;
	g_v.map_num_rows = 14;
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
	char direction = 0;

	i = 0;
	while (game->info->map[i])
	{
		j = 0;
		while (game->info->map[i][j])
		{
			if (game->info->map[i][j] == 'N' || game->info->map[i][j] == 'S' || game->info->map[i][j] == 'W'
				|| game->info->map[i][j] == 'E') {
					direction = game->info->map[i][j];
					game->info->map[i][j] = '0';
					game->p.row = i;
					game->p.col = j;
					game->p.x = game->p.col * g_v.title_size + g_v.title_size / 2;
					game->p.y = game->p.row * g_v.title_size + g_v.title_size / 2;
					return (direction);
				}
				j++;
		}
		i++;
	}
	return (0);
}

void	game_Setup(t_data *game) {
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
	game->ray.fov_angle = 60 * (M_PI / 180);
	game->ray.num_rays = g_v.map_num_width;
	game->ray.wall_hit_x = 0;
	game->ray.wall_hit_y = 0;
	game->ray.ray_angle = 0;
}

void	my_mlx_pixel_put(t_data *game, int x, int y, int color)
{
	char	*dst;

	if(x < 0 || x >= g_v.map_num_width || y < 0 || y >= g_v.map_num_height)
		return ;
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

void	render_line(t_data *game, double distance, double direction) {
	int k = 0;

	while (k < distance) {
		my_mlx_pixel_put(
			game,
			game->p.x + cos(direction) * k,
			game->p.y + sin(direction) * k,
			0xff0000);
		k++;
	}
}

void render_player (t_data *game) {
	rect(game, game->p.y - 3 , game->p.x - 3, 7, 0xff0000);
}

void	render_img (t_data *game) {
	int i = 0;
	int j;

	while (game->info->map[i]) {
		j = 0;
		while (game->info->map[i][j]) {
			if (game->info->map[i][j] == '0' || (i == game->p.row && j == game->p.col)) {
				rect(game, i * g_v.title_size, j * g_v.title_size, g_v.title_size -1, 0xD3D1D1);
			}
			else if (game->info->map[i][j] == '1')
				rect (game, i * g_v.title_size, j * g_v.title_size, g_v.title_size -1, 0x484747);
			j++;
		}
		i++;
	}
}

int	isWall (t_data *game, double x, double y, char sign) {
	if (x < 0 || x >= g_v.map_num_width || y < 0 || y >= g_v.map_num_height)
		return (-1);
	int x_index = floor(x / g_v.title_size);
	int y_index = floor(y / g_v.title_size);
	if (y_index < 0 || y_index > g_v.map_num_rows || x_index < 0 || x_index > (int)ft_strlen(game->info->map[y_index]))
		return (-1);
	if (game->info->map[y_index][x_index] != ' ' && game->info->map[y_index][x_index] != '1') {
		if (sign == 'y') {
			game->p.x = x;
			game->p.y = y;
		}
		return (0);
	}
	else
		return (1);
	return (-1);
}

double	distanceBetweenPointx (double x1, double y1, double x2, double y2) {
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double get_distance (double horzHitDistance, double vertHitDistance) {
	if (horzHitDistance == -1)
			return (vertHitDistance);
	else if (vertHitDistance == -1)
			return (horzHitDistance);
	if (horzHitDistance < vertHitDistance)
		return (horzHitDistance);
	return (vertHitDistance);
}

void	cast (t_data *game, t_wall wall) {
	double xintercept, yintercept = {0};
	double xstep, ystep = {0};
	double isDown, isUp = 0;
	double isRight, isLeft = 0;

	int HorizHit = 0;
	double HoriwallHitx = 0;
	double HoriwallHity = 0;
	isDown = game->ray.ray_angle > 0 && game->ray.ray_angle < M_PI;
	isUp = !isDown;

	isRight = game->ray.ray_angle < M_PI / 2 || game->ray.ray_angle > 3 * (M_PI / 2);
	isLeft = !isRight;
	yintercept = floor((game->p.y / g_v.title_size)) * g_v.title_size;
	if (isDown)
		yintercept += g_v.title_size;
	xintercept = game->p.x + ((yintercept - game->p.y) / tan(game->ray.ray_angle));

	ystep = g_v.title_size;
		if (isUp)
			ystep *= -1;
	xstep = g_v.title_size / tan(game->ray.ray_angle);
	if (isLeft && xstep > 0)
		xstep *= -1;
	if (isRight && xstep < 0)
		xstep *= -1;
	double nextHorix = xintercept;
	double nextHoriy = yintercept;
	int flag = 0;
	if (isUp)
		flag = 1;

	while (nextHorix >= 0 && nextHorix < g_v.map_num_width
		&& nextHoriy >= 0 && nextHoriy < g_v.map_num_height) {
		if (isWall(game, nextHorix, nextHoriy - flag, 'n') == 1) {
			HorizHit = 1;
			HoriwallHitx = nextHorix;
			HoriwallHity = nextHoriy;
			break ;

		}
		else if (isWall(game, nextHorix, nextHoriy - flag, 'n') == 0) {
			nextHorix += xstep;
			nextHoriy += ystep;
		}
		else
			break ;
	}
	flag = 0;

	// vertical
	int VertHit = 0;
	double vertiwallHitx = 0;
	double vertiwallHity = 0;

	xintercept = floor((game->p.x / g_v.title_size)) * g_v.title_size;
	if (isRight)
		xintercept += g_v.title_size;
	yintercept = game->p.y + ((xintercept - game->p.x) * tan(game->ray.ray_angle));

	xstep = g_v.title_size;
		if (isLeft)
			xstep *= -1;
	ystep = g_v.title_size * tan(game->ray.ray_angle);
	if (isUp && ystep > 0)
		ystep *= -1;
	if (isDown && ystep < 0)
		ystep *= -1;

	double	nextvertix = xintercept;
	double nextvertiy = yintercept;
	if (isLeft)
		flag = 1;

	while (nextvertix >= 0 && nextvertix < g_v.map_num_width
		&& nextvertiy >= 0 && nextvertiy < g_v.map_num_height) {
		if (isWall(game, nextvertix - flag, nextvertiy, 'n') == 1) {
			VertHit = 1;
			vertiwallHitx = nextvertix;
			vertiwallHity = nextvertiy;
			break ;
		}
		else if (isWall(game, nextvertix - flag, nextvertiy, 'n') == 0) {
			nextvertix += xstep;
			nextvertiy += ystep;
		}
		else
			break ;
	}

	// caluculate both distances
	double horzHitDistance = -1;
	double vertHitDistance = -1;
	double distance;
	if (HorizHit == 1)
		horzHitDistance = distanceBetweenPointx(game->p.x, game->p.y, HoriwallHitx, HoriwallHity);
	if (VertHit == 1)
		vertHitDistance = distanceBetweenPointx(game->p.x, game->p.y, vertiwallHitx, vertiwallHity);

	distance = get_distance (horzHitDistance, vertHitDistance);
	if (distance == vertHitDistance)
		wall.is_vertical = true;
	else
		wall.is_horisantal = true;
	wall.rays = distance;

	render_line(game, wall.rays, game->ray.ray_angle);
}

t_wall*	raycasting (t_data *game) {
	int i = 0;
	int columId = 0;
	t_wall *wall;
	game->ray.ray_angle = game->p.direction - (game->ray.fov_angle / 2);
	wall = (t_wall*)malloc(sizeof(t_wall) * game->ray.num_rays);
	while (i < game->ray.num_rays) {
		if (game->ray.ray_angle < 0)
			game->ray.ray_angle += M_PI * 2;
		else if (game->ray.ray_angle > M_PI * 2)
			game->ray.ray_angle -= M_PI * 2;
		cast(game, wall[i]);
		game->ray.ray_angle += game->ray.fov_angle / game->ray.num_rays;
		i++;
		columId++;
	}
	return (wall);
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

int main(int ac, char **av) {
	t_data game;

	init_gv();
	game.info = parsing (ac, av);
	game.mlx.mlx = mlx_init();
	game.mlx.mlx_win = mlx_new_window(game.mlx.mlx, 1054,  448, "Cub3d");
	game.img.img = mlx_new_image(game.mlx.mlx, 1054, 448);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, &game.img.line_length,
								&game.img.endian);
	game_Setup(&game);
	render_img(&game);
	render_player(&game);
	raycasting(&game);
	mlx_put_image_to_window(game.mlx.mlx, game.mlx.mlx_win, game.img.img, 0, 0);
	mlx_hook (game.mlx.mlx_win, 2, 0, key_pressed, &game);
	mlx_loop(game.mlx.mlx);
}