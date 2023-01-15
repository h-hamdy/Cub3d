/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:52:26 by fbouanan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/15 18:27:30 by hhamdy           ###   ########.fr       */
=======
/*   Updated: 2023/01/15 17:37:18 by fbouanan         ###   ########.fr       */
>>>>>>> 88ae42df480c2e0961d0bdba878397157813fc88
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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

<<<<<<< HEAD
	i = ft_strlen(next);
	j = ft_strlen(previous);
=======
	i = (int)ft_strlen(next);
	j = (int)ft_strlen(previous);
>>>>>>> 88ae42df480c2e0961d0bdba878397157813fc88
	if (now >= j || now >= i)
		print_error("Invalid map\n");
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
				print_error("Invalid map\n");
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
		mapv[j++] = map[i++];
	mapv[j] = NULL;
	return (mapv);
}

int	*rgb_tool(char *map)
{
	int		i;
	t_var	var;

	var.rgb = malloc(sizeof(int) * 3);
	var.tmp = ft_strdup("");
	i = skip_spaces(map) + 1;
	while (map[i] && !ft_isdigit(map[i]))
	{
		if (map[i] == ',')
			print_error("Invalid RGB\n");
		if (map[i] == ' ' || map[i] == '\t')
			i++;
	}
	while (map[i])
		var.tmp = ft_strjoin2(var.tmp, map[i++]);
	var.hold = ft_split(var.tmp, ',');
	i = 0;
	while (var.hold[i])
		i++;
	if (i != 3)
		print_error("Invalid RGB\n");
	var.rgb = rgb_tool_help(&var);
	free(var.tmp);
	return (var.rgb);
}
