/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:48:33 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/22 08:42:13 by hhamdy           ###   ########.fr       */
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
		printf("%f\n", cos(game->p.direction));
		printf("%f\n", sin(game->p.direction));
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
	if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
	{
		if (!is_wall(game, newx, game->p.y))
			game->p.x = newx;
		if (!is_wall(game, game->p.x, newy))
			game->p.y = newy;
		return (1);
	}
	return (0);
}

int	key_pressed(int key, t_data *game)
{
	double	newx;
	double	newy;

	if (key == TURN_LEFT || key == TURN_RIGHT)
		turn_direction (game, key);
	if (key == EXIT)
		exit (1);
	else if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
		walk_direction (game, key, &newx, &newy);
	normalize(game);
	if (key == TURN_LEFT || key == TURN_RIGHT
		|| check_movement(game, key, newx, newy))
	{
		game->wall = ft_calloc(sizeof(t_wall), game->ray.num_rays);
		raycasting(game);
		render_3d(game);
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win, \
			game->img.img, 0, 0);
		free(game->wall);
		game->wall = NULL;
	}
	return (0);
}
