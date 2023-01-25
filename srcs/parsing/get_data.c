/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:52:23 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/25 21:05:45 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

char	*parsing_help(t_info *info, char **av)
{
	char	*a;
	int		fd;
	char	*tmp;

	(void)info;
	a = ft_strdup("");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_error("Invalid path\n");
	tmp = ft_strdup("");
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		if (!ft_strcmp("\n", tmp))
		{
			free(tmp);
			tmp = ft_strdup(" \n");
		}
		a = ft_strjoin_frees1(a, tmp);
	}
	free(tmp);
	return (a);
}

void	check_map_path(char *path)
{
	char	*s;

	s = ft_strrchr(path, '.');
	if (!s)
		print_error("Invalid Path\n");
	if (ft_strcmp(s, ".cub"))
		print_error("Invalid Path\n");
}

t_info	*parsing(char **av)
{
	t_info	*info;
	char	**map;
	int		count;
	char	*a;

	info = malloc(sizeof(t_info));
	ft_initdata(info);
	check_map_path(av[1]);
	a = parsing_help(info, av);
	map = ft_split(a, '\n');
	free(a);
	count = ft_read_map(map, info);
	ft_parse_map(map, count, info);
	ft_free(map);
	return (info);
}
