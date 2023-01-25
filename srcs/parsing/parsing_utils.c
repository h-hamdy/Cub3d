/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:26:09 by hhamdy            #+#    #+#             */
/*   Updated: 2023/01/25 21:05:45 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

int	check_edges(char **map, int i, int j)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	if ((i == 0 || j == 0) || j == (int)ft_strlen(map[i]) - 1 || i == k - 1)
		return (1);
	return (0);
}

void	check_previous(int now, char *previous, char *next)
{
	int	j;
	int	i;

	i = ft_strlen(next);
	j = ft_strlen(previous);
	i = (int)ft_strlen(next);
	j = (int)ft_strlen(previous);
	if (now >= j || now >= i)
		print_error("ERROR\n");
}

void	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'W'
				&& map[i][j] != 'E' && map[i][j] != 'S' && map[i][j] != 'N' \
				&& map[i][j] != ' ')
				print_error("ERROR\n");
			j++;
		}
		i++;
	}
}

char	**alloc_map(char **map, int i)
{
	int		i2;
	int		j;
	char	**mapv;

	i2 = i;
	j = 0;
	while (map[i2])
	{
		i2++;
		j++;
	}
	mapv = malloc(sizeof(char *) * (j + 1));
	j = 0;
	while (map[i])
		mapv[j++] = ft_strdup(map[i++]);
	mapv[j] = NULL;
	return (mapv);
}

int	*rgb_tool(char *map)
{
	t_var	var;

	var.rgb = malloc(sizeof(int) * 3);
	var.tmp = ft_strdup("");
	var.i = skip_spaces(map) + 1;
	while (map[var.i] && !ft_isdigit(map[var.i]))
	{
		if (map[var.i] == ',')
			print_error("Invalid RGB\n");
		if (map[var.i] == ' ' || map[var.i] == '\t')
			var.i++;
	}
	while (map[var.i])
		var.tmp = ft_strjoin2(var.tmp, map[var.i++]);
	var.tmp = handel_end_spaces(var.tmp);
	var.hold = ft_split(var.tmp, ',');
	var.i = 0;
	while (var.hold[var.i])
		var.i++;
	if (var.i != 3)
		print_error("Invalid RGB\n");
	var.rgb = rgb_tool_help(&var);
	free(var.tmp);
	ft_free(var.hold);
	return (var.rgb);
}
