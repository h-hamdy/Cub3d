/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:52:38 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/19 17:24:41 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_elements	init_elements(void)
{
	t_elements	elm;

	elm.no = 0;
	elm.so = 0;
	elm.we = 0;
	elm.ea = 0;
	elm.f = 0;
	elm.c = 0;
	return (elm);
}

int	skip_spaces(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && !ft_isalnum(s[i]))
	{
		if (s[i] == ' ' || s[i] == '\t')
			count++;
		i++;
	}
	return (count);
}

int	check_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if ((path[i] == '.' && path[i + 1] == '/') || path[i] == '/')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_parse_map(char **map, int i, t_info *info)
{
	char	**mapv;

	mapv = alloc_map(map, i);
	check_map(mapv);
	ft_parse_map_help(mapv);
	check_player(mapv);
	info->map = mapv;
}

int	ft_read_map(char **map, t_info *info)
{
	int			i;
	int			j;
	int			s;
	t_elements	elm;

	i = 0;
	j = 0;
	s = 0;
	elm = init_elements();
	elm.count = 0;
	while (map[i])
	{
		if (!check_line(map[i]))
			s++;
		elm.count = ft_read_map_help(&elm, map, info, i);
		i++;
	}
	if (elm.count != 6)
		print_error("INVALID nuber of elements\n");
	return (elm.count + s);
}
