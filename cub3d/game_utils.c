# include "Cub3d.h"

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