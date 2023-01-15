/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:52:32 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/14 18:48:48 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	print_error(char *s)
{
	write(2, s, ft_strlen(s));
	exit (1);
}

void	ft_north(char *map, t_info *info)
{
	char	*tmp;
	int		k;
	int		i;
	int		count;

	i = 0;
	k = 0;
	tmp = ft_strdup("");
	count = check_path(map);
	if (count == -1)
		print_error("Invalid map\n");
	while (map[count])
		tmp = ft_strjoin2(tmp, map[count++]);
	if (!info->no)
		info->no = tmp;
	free(tmp);
}

void	ft_south(char *map, t_info *info)
{
	char	*tmp;
	int		k;
	int		i;
	int		count;

	i = 0;
	k = 0;
	tmp = ft_strdup("");
	count = check_path(map);
	if (count == -1)
		print_error("Invalid map\n");
	while (map[count])
		tmp = ft_strjoin2(tmp, map[count++]);
	if (!info->so)
		info->so = tmp;
	free(tmp);
}

void	ft_west(char *map, t_info *info)
{
	char	*tmp;
	int		k;
	int		i;
	int		count;

	i = 0;
	k = 0;
	tmp = ft_strdup("");
	count = check_path(map);
	if (count == -1)
		print_error("Invalid map\n");
	while (map[count])
		tmp = ft_strjoin2(tmp, map[count++]);
	if (!info->we)
		info->we = tmp;
	free(tmp);
}

void	ft_east(char *map, t_info *info)
{
	char	*tmp;
	int		k;
	int		i;
	int		count;

	i = 0;
	k = 0;
	tmp = ft_strdup("");
	count = check_path(map);
	if (count == -1)
		print_error("Invalid map\n");
	while (map[count])
		tmp = ft_strjoin2(tmp, map[count++]);
	if (!info->ea)
		info->ea = tmp;
	free(tmp);
}
