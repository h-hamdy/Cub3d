/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:22:31 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/17 14:30:24 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	render_3d(t_data *game)
{
	int		i;
	float	distencetowall;
	float	wallhight;
	double	startp;
	double	endp;
	int		j;

	i = 0;
	distencetowall = 0;
	wallhight = 0;
	startp = 0;
	endp = 0;
	while (i < game->ray.num_rays)
	{
		distencetowall = (WINDOW_WIDTH / 2) / (tan(game->ray.fov_angle / 2));
		wallhight = (g_v.title_size / game->wall[i].rays) * distencetowall;
		startp = (WINDOW_HEIGHT / 2) - (wallhight / 2);
		endp = startp + wallhight;
		j = 0;
		while (j < startp)
			my_mlx_pixel_put(game, i, j++, 0);
		while(j < endp)
			my_mlx_pixel_put(game, i, j++, 0xffffff);
		while(j < WINDOW_HEIGHT)
			my_mlx_pixel_put(game, i, j++, 0);
		i++;
	}
}
