#include "../Cub3d.h"

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
	{
		write(2, "Invalid map\n", 13);
		exit(1);
	}
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
	{
		write(2, "Invalid map\n", 13);
		exit(1);
	}
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
	{
		write(2, "Invalid map\n", 13);
		exit(1);
	}
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
	{
		write(2, "Invalid map\n", 13);
		exit(1);
	}
	while (map[count])
		tmp = ft_strjoin2(tmp, map[count++]);
	if (!info->ea)
		info->ea = tmp;
	free(tmp);
}
