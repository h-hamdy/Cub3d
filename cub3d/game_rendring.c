# include "Cub3d.h"

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
				rect(game, i * g_v.title_size, j * g_v.title_size, g_v.title_size, 0xD3D1D1);
			}
			else if (game->info->map[i][j] == '1')
				rect (game, i * g_v.title_size, j * g_v.title_size, g_v.title_size, 0x484747);
			j++;
		}
		i++;
	}
}