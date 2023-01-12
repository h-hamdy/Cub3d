#include "../Cub3d.h"

t_info	*parsing (int ac, char **av)
{
	t_info	*info;
	int		fd;
	char	*a;
	char	**map;
	char	*tmp;
	int		count;

	info = malloc(sizeof(t_info));
	if (ac > 1)
	{
		a = ft_strdup("");
		ft_initdata(info);
		fd = open(av[1], O_RDONLY);
		tmp = "";
		while (tmp)
		{
			tmp = get_next_line(fd);
			if (!tmp)
				break ;
			if (!ft_strcmp("\n", tmp))
			{
				free(tmp);
				tmp = ft_strdup(" \n");
			}
			a = ft_strjoin(a, tmp);
		}
		map = ft_split(a, '\n');
		count = ft_read_map(map, info);
		ft_parse_map(map, count, info);
	}
	return (info);
}