/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:22:31 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/22 17:01:31 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	int	rgb;

	rgb = (r << 16) + (g << 8) + b;
	return (rgb);
}

t_var	*gener_3d(t_data *game, t_var *v, int i)
{
	v->correct_ray_des = game->wall[i].rays * \
		cos(game->wall[i].ray_angle - game->p.direction);
	v->distencetowall = (WINDOW_WIDTH / 2) / (tan(game->ray.fov_angle / 2));
	v->wallhight = (g_v.title_size / v->correct_ray_des) * v->distencetowall;
	v->startp = (WINDOW_HEIGHT / 2) - (v->wallhight / 2);
	v->endp = v->startp + v->wallhight;
	return (v);
}

void	set_directions(t_data *game, t_img *img, t_var *v, int i)
{
	if (game->wall[i].is_vertical)
	{
		if (game->wall[i].is_left)
			img->addr = game->tex.we_addr;
		else
			img->addr = game->tex.ea_addr;
		v->t_offsetx = (int)game->wall[i].vertiwallhity % g_v.title_size;
	}
	else
	{
		if (game->wall[i].is_up)
			img->addr = game->tex.no_addr;
		else
			img->addr = game->tex.so_addr;
		v->t_offsetx = (int)game->wall[i].horiwallhitx % g_v.title_size;
	}
}

void	render_3d(t_data *game)
{
	int		i;
	int		j;
	t_var	v;
	t_img	img;

	i = 0;
	while (i < game->ray.num_rays)
	{
		gener_3d(game, &v, i);
		j = 0;
		while (j < v.startp)
			my_mlx_pixel_put(game, i, j++, game->tex.c_rgb);
		set_directions(game, &img, &v, i);
		while (j < v.endp)
		{
			v.t_offsety = (j - v.startp) * ((float)TEX_HEIGHT / v.wallhight);
			v.dst = img.addr + v.t_offsety * game->tex.img.line_length \
				+ v.t_offsetx * (game->tex.img.bits_per_pixel / 8);
			my_mlx_pixel_put(game, i, j++, *(int *)v.dst);
		}
		while (j < WINDOW_HEIGHT)
			my_mlx_pixel_put(game, i, j++, game->tex.f_rgb);
		i++;
	}
}
