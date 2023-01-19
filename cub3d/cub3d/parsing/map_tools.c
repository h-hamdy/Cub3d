/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:19:49 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/19 16:45:39 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	ft_parse_map_help(char **mapv)
{
	int		j;
	int		i;
	char	*elements;

	elements = "01WESN";
	i = -1;
	while (mapv[++i])
	{
		j = -1;
		while (mapv[i][++j])
		{
			if (mapv[i][j] == '0' || mapv[i][j] == 'W' || mapv[i][j] == 'E'
				|| mapv[i][j] == 'S' || mapv[i][j] == 'N')
			{
				if (check_edges(mapv, i, j))
					print_error("Invalid map\n");
				check_previous(j, mapv[i - 1], mapv[i + 1]);
				if (!ft_strchr(elements, mapv[i - 1][j])
					|| !ft_strchr(elements, mapv[i + 1][j]) \
					|| !ft_strchr(elements, mapv[i][j - 1]) \
					|| !ft_strchr(elements, mapv[i][j + 1]))
					print_error("Invalid map\n");
			}
		}
	}
}

int	ft_read_map_help(t_elements *elm, char **map, t_info *info, int i)
{
	int	j;

	j = skip_spaces(map[i]);
	if (!elm->no && (map[i][j] == 'N'
		&& map[i][j + 1] == 'O' && map[i][j + 2] == ' '))
		(ft_north(map[i], info), elm->count++, elm->no = 1);
	else if (!elm->so && (map[i][j] == 'S'
		&& map[i][j + 1] == 'O' && map[i][j + 2] == ' '))
		(ft_south(map[i], info), elm->count++, elm->so = 1);
	else if (!elm->we && (map[i][j] == 'W'
		&& map[i][j + 1] == 'E' && map[i][j + 2] == ' '))
		(ft_west(map[i], info), elm->count++, elm->we = 1);
	else if (!elm->ea && (map[i][j] == 'E'
		&& map[i][j + 1] == 'A' && map[i][j + 2] == ' '))
		(ft_east(map[i], info), elm->count++, elm->ea = 1);
	else if (!elm->f && (map[i][j] == 'F' && map[i][j + 1] == ' '))
		(ft_floor(map[i], info), elm->count++, elm->f = 1);
	else if (!elm->c && (map[i][j] == 'C' && map[i][j + 1] == ' '))
		(ft_ceilling(map[i], info), elm->count++, elm->f = 1);
	return (elm->count);
}

int	*rgb_tool_help(t_var *var)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (var->hold[i])
	{
		var->hold2 = ft_split(var->hold[i], ' ');
		k = 0;
		while (var->hold2[k])
			k++;
		if (k > 1)
			print_error("Invalid RGB\n");
		if (j < 3)
		{
			if (check_rgb(var->hold[i]))
				print_error("Invalid RGB\n");
			var->rgb[j] = ft_atoi(var->hold[i]);
			rgb_handling(var->rgb[j]);
			j++;
		}
		i++;
	}
	return (var->rgb);
}
