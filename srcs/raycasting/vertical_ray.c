/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:11:51 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/25 21:05:45 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

void	v_interception_count(t_data *game, t_wall *wall)
{
	wall->xintercept = floor((game->p.x / game->g_v.title_size)) \
		* game->g_v.title_size;
	if (wall->is_right)
		wall->xintercept += game->g_v.title_size;
	wall->yintercept = game->p.y + \
		((wall->xintercept - game->p.x) * tan(game->ray.ray_angle));
	wall->xstep = game->g_v.title_size;
	if (wall->is_left)
		wall->xstep *= -1;
	wall->ystep = game->g_v.title_size * tan(game->ray.ray_angle);
	if (wall->is_up && wall->ystep > 0)
		wall->ystep *= -1;
	if (wall->is_down && wall->ystep < 0)
		wall->ystep *= -1;
}

void	v_inisialize(t_wall *wall, int *flag)
{
	wall->vertiwallhitx = 0;
	wall->vertiwallhity = 0;
	*flag = 0;
	if (wall->is_left)
		*flag = 1;
}

bool	vertical_ray(t_data *game, t_wall *wall)
{
	int		flag;
	double	nextvertix;
	double	nextvertiy;

	v_interception_count(game, wall);
	v_inisialize(wall, &flag);
	nextvertix = wall->xintercept;
	nextvertiy = wall->yintercept;
	while (nextvertix >= 0 && nextvertix < game->g_v.map_num_width
		&& nextvertiy >= 0 && nextvertiy < game->g_v.map_num_height)
	{
		if (is_wall(game, nextvertix - flag, nextvertiy) == 1)
		{
			wall->vertiwallhitx = nextvertix;
			wall->vertiwallhity = nextvertiy;
			return (true);
		}
		else if (is_wall(game, nextvertix - flag, nextvertiy) == 0)
			if_not_wall(wall, &nextvertix, &nextvertiy);
		else
			break ;
	}
	return (false);
}
