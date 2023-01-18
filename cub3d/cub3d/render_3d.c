/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:22:31 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/18 13:27:48 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	render_3d(t_data *game)
{
	int		i;
	float	distencetowall;
	float	wallhight;
	float	startp;
	float	endp;
	int		j;
	float	correct_ray_des;
	// void	*w;
	
	char	*dst;
	int		t_offsetx;
	int		t_offsety;
	int		x;
	int		y;
	struct s_img	img;
	i = 0;
	distencetowall = 0;
	correct_ray_des = 0;
	wallhight = 0;
	startp = 0;
	endp = 0;
	img.img = mlx_xpm_file_to_image(game->mlx.mlx, "tex/wall.xpm", &x, &y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (i < game->ray.num_rays)
	{
		correct_ray_des = game->wall[i].rays * cos(game->ray.ray_angle - game->p.direction);
		distencetowall = (WINDOW_WIDTH / 2) / (tan(game->ray.fov_angle / 2));
		wallhight = (g_v.title_size / correct_ray_des) * distencetowall;
		startp = (WINDOW_HEIGHT / 2) - (wallhight / 2);
		endp = startp + wallhight;

		j = 0;
		while (j < startp)
			my_mlx_pixel_put(game, i, j++, 0xffff);
		if (game->wall[i].is_vertical)
			t_offsetx = (int)game->wall[i].vertiwallhity % g_v.title_size;
		else
			t_offsetx = (int)game->wall[i].horiwallhitx % g_v.title_size;
		while(j < endp)
		{
			t_offsety = (j - startp) * ((float)TEX_HEIGHT / wallhight);
			dst = img.addr + t_offsety * img.line_length + t_offsetx * (img.bits_per_pixel / 8);
			my_mlx_pixel_put(game, i, j++, *( int *)dst);
		}
		while(j < WINDOW_HEIGHT)  
			my_mlx_pixel_put(game, i, j++, 0xffffff);
		i++;
	}
}
