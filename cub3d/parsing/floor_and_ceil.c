/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:52:20 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/14 17:52:21 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	check_line(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_rgb(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	rgb_handling(int rgb)
{
	if (rgb > 255 || rgb < 0)
		print_error("the rgb is out of range\n");
}

void	ft_floor(char *map, t_info *info)
{
	if (!info->f)
		info->f = rgb_tool(map);
}

void	ft_ceilling(char *map, t_info *info)
{
	if (!info->c)
		info->c = rgb_tool(map);
}
