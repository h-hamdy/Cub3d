/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:26:56 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/17 14:36:15 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

double	distance_between_pointx(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double	get_distance(double horzHitDistance, double vertHitDistance)
{
	if (horzHitDistance == -1)
		return (vertHitDistance);
	else if (vertHitDistance == -1)
		return (horzHitDistance);
	if (horzHitDistance < vertHitDistance)
		return (horzHitDistance);
	return (vertHitDistance);
}
