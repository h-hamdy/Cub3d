/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:09:32 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/24 15:28:13 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	count_rows(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	count_cols(char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > ret)
			ret = j;
		i++;
	}
	return (ret);
}

void	init_gv(t_data *game)
{
	game->g_v.title_size = 32;
	game->g_v.map_num_rows = count_rows(game->info->map);
	game->g_v.map_num_cols = count_cols(game->info->map);
	game->g_v.prev_x = 0;
	game->g_v.map_num_width = game->g_v.map_num_cols * game->g_v.title_size;
	game->g_v.map_num_height = game->g_v.map_num_rows * game->g_v.title_size;
}

void	game_setup(t_data *game)
{
	char	direction;

	direction = get_direction(game);
	if (direction == 'N')
		game->p.direction = 3 * (M_PI / 2);
	else if (direction == 'S')
		game->p.direction = M_PI / 2;
	else if (direction == 'E')
		game->p.direction = 0;
	else
		game->p.direction = M_PI;
	game->p.move_speed = 7.0;
	game->p.rotation_speed = 5 * (M_PI / 180);
	game->ray.fov_angle = 60 * (M_PI / 180);
	game->ray.num_rays = 1056;
	game->ray.wall_hit_x = 0;
	game->ray.wall_hit_y = 0;
	game->ray.ray_angle = 0;
}

int	ft_exit(void)
{
	exit (0);
}
