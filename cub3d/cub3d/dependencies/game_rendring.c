/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_rendring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:12:32 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/22 05:52:24 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	my_mlx_pixel_put(t_data *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= g_v.map_num_width || y < 0 || y >= g_v.map_num_height)
		return ;
	dst = game->img.addr + \
		(y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	rect(t_data *game, int i, int j, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < g_v.title_size)
	{
		y = 0;
		while (y < g_v.title_size)
		{
			my_mlx_pixel_put(game, j + y, i + x, color);
			y++;
		}
		x++;
	}
}

void	render_line(t_data *game, double distance, double direction)
{
	int	k;

	k = 0;
	while (k < distance)
	{
		my_mlx_pixel_put(
			game,
			game->p.x + cos(direction) * k,
			game->p.y + sin(direction) * k,
			0xff0000);
		k++;
	}
}

void	render_player(t_data *game, int j, int i, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < 11)
	{
		y = 0;
		while (y < 11)
		{
			my_mlx_pixel_put(game, j + y, i + x, color);
			y++;
		}
		x++;
	}
}

void	render_img(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->info->map[i])
	{
		j = 0;
		while (game->info->map[i][j])
		{
			if (game->info->map[i][j] == '0'
				|| (i == game->p.row && j == game->p.col))
				rect(game, i * g_v.title_size,
					j * g_v.title_size, 0xD3D1D1);
			else if (game->info->map[i][j] == '1')
				rect(game, i * g_v.title_size,
					j * g_v.title_size, 0x484747);
			j++;
		}
		i++;
	}
}
