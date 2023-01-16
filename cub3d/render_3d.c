/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:22:31 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/16 22:29:11 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	render_3d(t_data *game)
{
	int		i;
	float	distencetowall;
	float	wallhight;
	double		startp;
	double		endp;
	int		j;
	
	i = 0;
	distencetowall = 0;
	wallhight = 0;
	startp = 0;
	endp = 0;
	while (i < game->ray.num_rays)
	{
		// printf("here %f\n",  wall[i].rays);
		distencetowall = (WINDOW_WIDTH / 2) / (tan(game->ray.fov_angle / 2));
		// printf("%f\n", wall[i].rays);
		// exit(1);
		wallhight = (g_v.title_size / game->wall[i].rays) * distencetowall;
		// printf("%f, %d, %f\n", wallhight, WINDOW_HEIGHT, distencetowall);
		// exit (1);
		startp = (WINDOW_HEIGHT / 2) - (wallhight / 2);
		endp = startp + wallhight;
		// printf("%d %d\n", startp, endp);
		
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
