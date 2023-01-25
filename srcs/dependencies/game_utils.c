/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:50:59 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/25 21:05:45 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

int	check_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

char	inisialze(t_data *game, int i, int j)
{
	char	direction;

	direction = game->info->map[i][j];
	game->info->map[i][j] = '0';
	game->p.row = i;
	game->p.col = j;
	game->p.x = game->p.col * game->g_v.title_size + game->g_v.title_size / 2;
	game->p.y = game->p.row * game->g_v.title_size + game->g_v.title_size / 2;
	game->p.x = game->p.col * game->g_v.title_size + game->g_v.title_size / 2;
	game->p.y = game->p.row * game->g_v.title_size + game->g_v.title_size / 2;
	return (direction);
}

char	get_direction(t_data *game)
{
	int		i;
	int		j;

	i = 0;
	while (game->info->map[i])
	{
		j = 0;
		while (game->info->map[i][j])
		{
			if (check_direction(game->info->map[i][j]))
				return (inisialze(game, i, j));
			j++;
		}
		i++;
	}
	return (0);
}

int	is_wall(t_data *game, double x, double y)
{
	int	x_index;
	int	y_index;

	if (x < 0 || x >= game->g_v.map_num_width || y < 0 \
		|| y >= game->g_v.map_num_height)
		return (-1);
	x_index = floor(x / game->g_v.title_size);
	y_index = floor(y / game->g_v.title_size);
	if (y_index < 0 || y_index > game->g_v.map_num_rows
		|| x_index < 0 || x_index > (int)ft_strlen(game->info->map[y_index]))
		return (-1);
	if (game->info->map[y_index][x_index] != ' '
		&& game->info->map[y_index][x_index] != '1')
		return (0);
	else
		return (1);
	return (-1);
}
