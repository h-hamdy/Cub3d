/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <fbouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:52:32 by fbouanan          #+#    #+#             */
/*   Updated: 2023/01/25 21:05:45 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cub3d.h"

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
		print_error("ERROR\n");
	while (map[count])
		tmp = ft_strjoin2(tmp, map[count++]);
	tmp = handel_end_spaces(tmp);
	if (!info->no)
		info->no = tmp;
	else
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
		print_error("ERROR\n");
	while (map[count])
		tmp = ft_strjoin2(tmp, map[count++]);
	tmp = handel_end_spaces(tmp);
	if (!info->so)
		info->so = tmp;
	else
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
		print_error("ERROR\n");
	while (map[count])
		tmp = ft_strjoin2(tmp, map[count++]);
	tmp = handel_end_spaces(tmp);
	if (!info->we)
		info->we = tmp;
	else
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
		print_error("ERROR\n");
	while (map[count])
		tmp = ft_strjoin2(tmp, map[count++]);
	tmp = handel_end_spaces(tmp);
	if (!info->ea)
		info->ea = tmp;
	else
		free(tmp);
}
