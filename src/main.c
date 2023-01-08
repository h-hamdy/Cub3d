# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

typedef struct {
	int x;
	int y;
	double direction;
	float moveSpeed;
	double rotationSpeed;
} Player;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

const	int	TITLE_SIZE = 60;
const	int	MAP_NUM_ROWS = 12;
const	int	MAP_NUM_COLS = 15;
const	int	MAP_NUM_WIDTH = MAP_NUM_COLS * TITLE_SIZE;
const	int	MAP_NUM_HEIGHT = MAP_NUM_ROWS * TITLE_SIZE;


char str[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '1', '0', 'N', '0', '0', '0', '1', '1', '1', '0', '0', '1'},
	{'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '1', '1', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	rect(t_data *img, int i, int j, int len, int color)
{
	for (int l = 0; l < len; l++) {
		for (int k = 0; k < len; k++) {
			my_mlx_pixel_put(img, j + k, i + l, color);
		}
	}
}

void	PlayerSetup(char direction, Player *p) {
	if (direction == 'N')
		p->direction = 3 * (M_PI / 2);
	else if (direction == 'S')
		p->direction = M_PI / 2;
	else if (direction == 'E')
		p->direction = 0;
	else
		p->direction = M_PI;
	p->moveSpeed = 5.0;
	p->rotationSpeed = 3 * (M_PI / 180);
}

int main(void){
	void	*mlx;
	void	*mlx_win;
	Player 	p;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, MAP_NUM_WIDTH,  MAP_NUM_HEIGHT, "Cub3d");
	img.img = mlx_new_image(mlx, MAP_NUM_WIDTH, MAP_NUM_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (int i = 0; i < MAP_NUM_ROWS; i++) {
		for (int j = 0; j < MAP_NUM_COLS; j++) {
			if (str[i][j] == '0' || str[i][j] == 'N' || str[i][j] == 'W' || str[i][j] == 'E' || str[i][j] == 'S') {
				rect(&img, i * TITLE_SIZE, j * TITLE_SIZE, TITLE_SIZE - 1, 0xD3D1D1);
				if (str[i][j] == 'N' || str[i][j] == 'W' || str[i][j] == 'E' || str[i][j] == 'S')
				{
					PlayerSetup(str[i][j], &p);
					p.x = j * TITLE_SIZE + TITLE_SIZE / 2;
					p.y = i * TITLE_SIZE + TITLE_SIZE / 2;
					rect(&img, p.x - 3, p.y - 3, 7, 0xff0000);
					for (int k = 0; k < 30; k++) {
						my_mlx_pixel_put(&img, p.x, p.y - k, 0xff0000);
					}
				}
			}
			else if (str[i][j] == '1')
				rect (&img, i * TITLE_SIZE, j * TITLE_SIZE, TITLE_SIZE - 1, 0x484747);
		}
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	}
	mlx_loop(mlx);
}