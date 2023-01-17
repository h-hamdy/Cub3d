/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:48:33 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/17 14:36:23 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	normalize(t_data *game)
{
	if (game->p.direction < 0)
		game->p.direction += M_PI * 2;
	else if (game->p.direction > M_PI * 2)
		game->p.direction -= M_PI * 2;
}

void	turn_direction(t_data *game, int key)
{
	if (key == EXIT)
		exit (1);
	if (key == TURN_LEFT)
		game->p.direction += -1 * game->p.rotation_speed;
	else if (key == TURN_RIGHT)
		game->p.direction += 1 * game->p.rotation_speed;
}

void	walk_direction(t_data *game, int key, double *newx, double *newy)
{
	double	direction;

	direction = game->p.direction + M_PI / 2;
	if (key == UP)
	{
		*newx = game->p.x + cos(game->p.direction) * game->p.move_speed;
		*newy = game->p.y + sin(game->p.direction) * game->p.move_speed;
	}
	else if (key == DOWN)
	{
		*newx = game->p.x - cos(game->p.direction) * game->p.move_speed;
		*newy = game->p.y - sin(game->p.direction) * game->p.move_speed;
	}
	else if (key == RIGHT)
	{
		*newx = game->p.x + cos(direction) * game->p.move_speed;
		*newy = game->p.y + sin(direction) * game->p.move_speed;
	}
	else if (key == LEFT)
	{
		*newx = game->p.x - cos(direction) * game->p.move_speed;
		*newy = game->p.y - sin(direction) * game->p.move_speed;
	}
}

int	check_movement(t_data *game, int key, double newx, double newy)
{
	return (((key == UP || key == DOWN || key == RIGHT || key == LEFT) \
		&& !is_wall(game, newx, game->p.y, 'y') \
		&& !is_wall(game, game->p.x, newy, 'y')));
}

int	key_pressed(int key, t_data *game)
{
	double	newx;
	double	newy;

	if (key == EXIT || key == TURN_LEFT || key == TURN_RIGHT)
		turn_direction (game, key);
	else if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
		walk_direction (game, key, &newx, &newy);
	normalize(game);
	if (key == TURN_LEFT || key == TURN_RIGHT
		|| check_movement(game, key, newx, newy))
	{
		game->wall = raycasting(game);
		render_3d(game);
		mlx_put_image_to_window(game->mlx.mlx, \
			game->mlx.mlx_win, game->img.img, 0, 0);
	}
	return (0);
}
