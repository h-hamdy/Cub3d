# include "Cub3d.h"

void	init_gv()
{
	g_v.title_size = 32;
	g_v.map_num_rows = 14;
	g_v.map_num_cols = 33;
	g_v.map_num_width = g_v.map_num_cols * g_v.title_size;
	g_v.map_num_height = g_v.map_num_rows * g_v.title_size;
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