#include <mlx.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1900, 1000, "Hello world!");
	img.img = mlx_new_image(mlx, 1900, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

// 123 left
// 124 right

// 13 up
// 1 down
// 2 right
// 0 left

// for (int k = 0; k < 30; k++) {
// 						my_mlx_pixel_put(
// 							game,
// 							game->p.x + cos(game->p.direction) * k,
// 							game->p.y + sin(game->p.direction) * k,
// 							0xff0000);
// 					}


// int		key_pressed (int key, Player p, t_data img) {
// 	printf("%d\n", key);
// 	// if (key == 123)
// 	// 	p.direction += p.turnDirection * p.moveSpeed;
// 	// else
// 	// 	p.direction += p.direction * p.moveSpeed;
// 	// for (int k = 0; k < 30; k++) {
// 	// 	my_mlx_pixel_put(
// 	// 		&img,
// 	// 		p.x + cos(p.direction) * k,
// 	// 		p.y + sin(p.direction) * k,
// 	// 		0xff0000);
// 	// }
// 	return (0);
// }