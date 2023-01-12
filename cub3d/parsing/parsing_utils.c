#include "../Cub3d.h"

int	check_edges(char **map, int i, int j)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	if ((i == 0 || j == 0) || (size_t)j == ft_strlen(map[i]) - 1 || i == k - 1)
		return (1);
	return (0);
}

void	check_previous(int now, char *previous, char *next)
{
	int	j;
	int	i;

	i = ft_strlen(next);
	j = ft_strlen(previous);
	if (now > j || now > i)
	{
		write(2, "Invalid map\n", 13);
		exit (1);
	}
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
			{
				printf("%s\n", map[i]);
				write(2, "Invalid symbols\n", 17);
				exit (1);
			}
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
