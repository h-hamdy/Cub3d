#include "../Cub3d.h"

int	check_line(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	rgb_handling(int rgb)
{
	if (rgb > 255 || rgb < 0)
	{
		write(2, "the rgb is out of range\n", 25);
		exit (1);
	}
}

void	ft_floor(char *map, t_info *info)
{
	int		i;
	int		j;
	char	*tmp;
	char	**hold;
	char	**hold2;
	int		f_rgb[3];

	tmp = ft_strdup("");
	i = skip_spaces(map) + 1;
	while (map[i] && !ft_isdigit(map[i]))
	{
		if (map[i] == ',')
		{
			write(2, "Invalid RGB\n", 13);
			exit(1);
		}
		if (map[i] == ' ' || map[i] == '\t')
			i++;
	}
	while (map[i])
		tmp = ft_strjoin2(tmp, map[i++]);
	hold = ft_split(tmp, ',');
	i = 0;
	while (hold[i])
		i++;
	if (i != 3)
	{
		write(2, "Invalid RGB\n", 13);
		exit (1);
	}
	i = 0;
	j = 0;
	while (hold[i])
	{
		hold2 = ft_split(hold[i], ' ');
		int	k;

		k = 0;
		while (hold2[k])
			k++;
		if (k > 1)
		{
			write(2, "Invalid RGB\n", 13);
			exit(1);
		}
		if (j < 3)
		{
			f_rgb[j] = ft_atoi(hold[i]);
			rgb_handling(f_rgb[j]);
			j++;
		}
		i++;
	}
	if (!info->f)
		info->f = f_rgb;
	free(tmp);
}

void	ft_ceilling(char *map, t_info *info)
{
	int		i;
	int		j;
	char	*tmp;
	char	**hold;
	char	**hold2;
	int		c_rgb[3];
	int		k;

	tmp = ft_strdup("");
	i = skip_spaces(map) + 1;
	while (map[i] && !ft_isdigit(map[i]))
	{
		if (map[i] == ',')
		{
			write(2, "Invalid RGB\n", 13);
			exit (1);
		}
		if (map[i] == ' ' || map[i] == '\t')
			i++;
	}
	while (map[i])
		tmp = ft_strjoin2(tmp, map[i++]);
	hold = ft_split(tmp, ',');
	i = 0;
	while (hold[i])
		i++;
	if (i != 3)
	{
		write(2, "Invalid RGB\n", 13);
		exit (1);
	}
	i = 0;
	j = 0;
	while (hold[i])
	{
		hold2 = ft_split(hold[i], ' ');
		k = 0;
		while (hold2[k])
			k++;
		if (k > 1)
		{
			write(2, "Invalid RGB\n", 13);
			exit(1);
		}
		if (j < 3)
		{
			c_rgb[j] = ft_atoi(hold[i]);
			rgb_handling(c_rgb[j]);
			j++;
		}
		i++;
	}
	if (!info->c)
		info->c = c_rgb;
	free(tmp);
}
