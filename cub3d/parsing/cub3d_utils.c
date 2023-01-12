#include "../Cub3d.h"

char	*ft_strjoin2(char *s, char c)
{
	int		i;
	char	*r;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	r = malloc(sizeof(char) * i + 2);
	if (!r)
		return (NULL);
	i = 0;
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	r[i] = c;
	r[i + 1] = '\0';
	free(s);
	return (r);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	check_player(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0; 
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		write(2, "Invalid player\n", 16);
		exit (1);
	}
}

void	ft_initdata(t_info *info)
{
	info->no = 0;
	info->so = 0;
	info->we = 0;
	info->ea = 0;
	info->f = 0;
	info->c = 0;
}
