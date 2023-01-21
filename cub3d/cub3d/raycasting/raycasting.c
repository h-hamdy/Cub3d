/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:58:20 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/20 18:00:42 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	inisial_direction(t_data *game, t_wall *wall)
{
	wall->is_down = (game->ray.ray_angle > 0 && game->ray.ray_angle < M_PI);
	wall->is_up = !wall->is_down;
	wall->is_right = (game->ray.ray_angle < M_PI / 2 \
		|| game->ray.ray_angle > 3 * (M_PI / 2));
	wall->is_left = !wall->is_right;
}

void	calculate_distances(t_data *game, t_wall *wall)
{
	double	horzhitdistance;
	double	verthitdistance;
	double	distance;

	horzhitdistance = -1;
	verthitdistance = -1;
	if (wall->horiz_hit)
		horzhitdistance = distance_between_pointx(game->p.x, \
			game->p.y, wall->horiwallhitx, wall->horiwallhity);
	if (wall->verti_hit)
		verthitdistance = distance_between_pointx(game->p.x, \
			game->p.y, wall->vertiwallhitx, wall->vertiwallhity);
	distance = get_distance (horzhitdistance, verthitdistance);
	if (distance == verthitdistance)
		wall->is_vertical = true;
	else
		wall->is_horisantal = true;
	wall->rays = distance;
}

t_wall	cast(t_data *game, t_wall wall)
{
	inisial_direction(game, &wall);
	wall.horiz_hit = horizontal_ray(game, &wall);
	wall.verti_hit = vertical_ray (game, &wall);
	calculate_distances(game, &wall);
	return (wall);
}

t_wall	*raycasting(t_data *game)
{
	int		i;
	int		colum_id;
	t_wall	*wall;

	i = 0;
	colum_id = 0;
	wall = (t_wall *)malloc(sizeof(t_wall) * game->ray.num_rays);
	game->ray.ray_angle = game->p.direction - (game->ray.fov_angle / 2);
	while (i < game->ray.num_rays)
	{
		if (game->ray.ray_angle < 0)
			game->ray.ray_angle += M_PI * 2;
		else if (game->ray.ray_angle > M_PI * 2)
			game->ray.ray_angle -= M_PI * 2;
		wall[colum_id] = cast(game, wall[i]);
		wall[colum_id].ray_angle = game->ray.ray_angle;
		game->ray.ray_angle += game->ray.fov_angle / game->ray.num_rays;
		i++;
		colum_id++;
	}
	return (wall);
}
