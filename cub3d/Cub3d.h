#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>

# include "libft/libft.h"

#define BUFFER_SIZE 1024
#define WINDOW_WIDTH 1056
#define WINDOW_HEIGHT 448

# define EXIT 		53
# define TURN_LEFT	123
# define TURN_RIGHT	124
# define UP			13
# define DOWN		1
# define RIGHT		2
# define LEFT		0

typedef struct g_var
{
	int title_size;
	int map_num_rows;
	int map_num_cols;
	double map_num_width;
	double map_num_height;
}	g_var;

g_var	g_v;

struct Player {
	double x;
	double y;
	int row;
	int col;
	double direction;
	float moveSpeed;
	double rotationSpeed;
};

struct s_rays {
	double fov_angle;
	double ray_angle;
	int		 num_rays;
	double wall_hit_x;
	double wall_hit_y;
};

struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct 	my_mlx {
	void	*mlx;
	void	*mlx_win;
};

typedef struct infos
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			*f;
	int			*c;
	char		**map;
	int			x;
	int			y;
	
}	t_info;

typedef struct elements
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
	int	count;
} t_elements;

typedef struct s_data
{
	struct Player p;
	struct s_img img;
	struct my_mlx mlx;
	t_info *info;
	struct s_rays ray;
}			t_data;

typedef	struct s_vars
{
	char	*tmp;
	char	**hold;
	char	**hold2;
	int		*rgb;
} t_var;

// PARSING
char	*get_next_line(int fd);
char	*ft_strjoin2(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
void	ft_parse_map(char **map, int i, t_info *info);
int		ft_read_map(char **map, t_info *info);
void	ft_initdata(t_info *info);
void	check_player(char **map);
int		check_edges(char **map, int i, int j);
void	check_previous(int now, char *previous, char *next);
void	check_map(char **map);
char	**alloc_map(char **map, int i);
int		check_path(char *path);
int		check_line(char *map);
int		skip_spaces(char *s);
void	ft_floor(char *map, t_info *info);
void	ft_ceilling(char *map, t_info *info);
void	ft_east(char *map, t_info *info);
void	ft_west(char *map, t_info *info);
void	ft_south(char *map, t_info *info);
void	ft_north(char *map, t_info *info);
t_info	*parsing (int ac, char **av);
int		*count_map(char **map ,int *c);
void	data(t_info *info);
int		*rgb_tool(char *map);
int		check_rgb(char *s);
void	rgb_handling(int rgb);
void	print_error(char *s);
void	ft_parse_map_help(char **mapv);
int		ft_read_map_help(t_elements *elm, char **map, t_info *info, int i);
int		*rgb_tool_help(t_var *var);

#endif