/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:12:00 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/20 03:32:27 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	h_interception_count(t_data *game, t_wall *wall)
{
	wall->yintercept = floor((game->p.y / g_v.title_size)) * g_v.title_size;
	if (wall->is_down)
		wall->yintercept += g_v.title_size;
	wall->xintercept = game->p.x + \
		((wall->yintercept - game->p.y) / tan(game->ray.ray_angle));
	wall->ystep = g_v.title_size;
	if (wall->is_up)
		wall->ystep *= -1;
	wall->xstep = g_v.title_size / tan(game->ray.ray_angle);
	if (wall->is_left && wall->xstep > 0)
		wall->xstep *= -1;
	if (wall->is_right && wall->xstep < 0)
		wall->xstep *= -1;
}

void	h_inisialize(t_wall *wall, int *flag)
{
	wall->horiwallhitx = 0;
	wall->horiwallhity = 0;
	*flag = 0;
	if (wall->is_up)
		*flag = 1;
}

void	if_not_wall(t_wall *wall, double *next_x, double *next_y)
{
	*next_x += wall->xstep;
	*next_y += wall->ystep;
}

bool	horizontal_ray(t_data *game, t_wall *wall)
{
	int		flag;
	double	next_horix;
	double	next_horiy;

	h_interception_count(game, wall);
	h_inisialize(wall, &flag);
	next_horix = wall->xintercept;
	next_horiy = wall->yintercept;
	while (next_horix >= 0 && next_horix < g_v.map_num_width
		&& next_horiy >= 0 && next_horiy < g_v.map_num_height)
	{
		if (is_wall(game, next_horix, next_horiy - flag) == 1)
		{
			wall->horiwallhitx = next_horix;
			wall->horiwallhity = next_horiy;
			return (true);
		}
		else if (!is_wall(game, next_horix, next_horiy - flag))
			if_not_wall(wall, &next_horix, &next_horiy);
		else
			break ;
	}
	return (false);
}
