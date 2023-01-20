/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:09:32 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/20 04:13:53 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	init_gv(void)
{
	g_v.title_size = 32;
	g_v.map_num_rows = 14;
	g_v.map_num_cols = 33;
	g_v.map_num_width = g_v.map_num_cols * g_v.title_size;
	g_v.map_num_height = g_v.map_num_rows * g_v.title_size;
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
	game->ray.num_rays = g_v.map_num_width;
	game->ray.wall_hit_x = 0;
	game->ray.wall_hit_y = 0;
	game->ray.ray_angle = 0;
}
