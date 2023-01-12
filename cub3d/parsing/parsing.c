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
	int		j;
	char	*elements;
	char	**mapv;

	mapv = alloc_map(map, i);
	check_map(mapv);
	elements = "01WESN";
	i = 0;
	while (mapv[i])
	{
		j = 0;
		while (mapv[i][j])
		{
			if (mapv[i][j] == '0' || mapv[i][j] == 'W' || mapv[i][j] == 'E'
				|| mapv[i][j] == 'S' || mapv[i][j] == 'N')
			{
				// check_zero()
				if (check_edges(mapv, i, j))
				{
					write(2, "Invalid map\n", 13);
					exit (1);
				}
				check_previous(j, mapv[i - 1], mapv[i + 1]);
				if (!ft_strchr(elements, mapv[i - 1][j]) || !ft_strchr(elements, mapv[i + 1][j])
					|| !ft_strchr(elements, mapv[i][j - 1]) || !ft_strchr(elements, mapv[i][j + 1]))
				{
					write(2, "Invalid map\n", 13);
					exit (1);
				}
			}
			j++;
		}
		i++;
	}
	check_player(mapv);
	info->map = mapv;
}

int	ft_read_map(char **map, t_info *info)
{
	int			i;
	int			j;
	int			s;
	int			count;
	t_elements	elm;

	i = 0;
	j = 0;
	s = 0;
	count = 0;
	elm = init_elements();
	while (map[i])
	{
		j = skip_spaces(map[i]);
		if (!check_line(map[i]))
			s++;
		else if (!elm.no && (map[i][j] == 'N' && map[i][j + 1] == 'O' && map[i][j + 2] == ' '))
			ft_north(map[i], info),count++, elm.no = 1;
		else if (!elm.so && (map[i][j] == 'S' && map[i][j + 1] == 'O' && map[i][j + 2] == ' '))
			ft_south(map[i], info),count++, elm.so = 1;
		else if (!elm.we && (map[i][j] == 'W' && map[i][j + 1] == 'E' && map[i][j + 2] == ' '))
			ft_west(map[i], info),count++, elm.we = 1;
		else if (!elm.ea && (map[i][j] == 'E' && map[i][j + 1] == 'A' && map[i][j + 2] == ' '))
			ft_east(map[i], info),count++, elm.ea = 1;
		else if (!elm.f && (count >= 4) && (map[i][j] == 'F' && map[i][j + 1] == ' '))
			ft_floor(map[i], info),count++, elm.f = 1;
		else if (!elm.c && (count >= 4) && (map[i][j] == 'C' && map[i][j + 1] == ' '))
			ft_ceilling(map[i], info),count++, elm.f = 1;
		i++;
	}
	if (count != 6)
	{
		write(2, "INVALID nuber of elements\n", 27);
		exit(1);
	}	
	return (count + s);
}
