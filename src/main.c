# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

const	int	TITLE_SIZE = 60;
const	int	MAP_NUM_ROWS = 12;
const	int	MAP_NUM_COLS = 15;
const	int	MAP_NUM_WIDTH = MAP_NUM_COLS * TITLE_SIZE;
const	int	MAP_NUM_HEIGHT = MAP_NUM_ROWS * TITLE_SIZE;


char str[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', 'P', '0', '0', '0', '1', '1', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
};


void	rect(void *mlx, void *mlx_win, int i, int j, int len, int color)
{
	for (int l = 0; l < len; l++) {
		for (int k = 0; k < len; k++) {
			mlx_pixel_put(mlx, mlx_win, j + k, i + l, color);
		}
	}
}

int main(void){
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, MAP_NUM_WIDTH,  MAP_NUM_HEIGHT, "Cub3d");
	for (int i = 0; i < MAP_NUM_ROWS; i++) {
		for (int j = 0; j < MAP_NUM_COLS; j++) {
			if (str[i][j] == '0' || str[i][j] == 'P') {
				rect(mlx, mlx_win, i * TITLE_SIZE, j * TITLE_SIZE, TITLE_SIZE - 1, 0xffffff);
				if (str[i][j] == 'P')
					rect(mlx, mlx_win,
					j * TITLE_SIZE + TITLE_SIZE / 2 - 4,
					i * TITLE_SIZE + TITLE_SIZE / 2 - 4,
					8, 0xff0000);
			}
		}
	}
	mlx_loop(mlx);
}