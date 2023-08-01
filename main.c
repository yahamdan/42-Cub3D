#include "cub.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	//if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	//{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	//}
}

int main(int ac, char **av)
{
    t_cub   map;

    map.mlx_ = mlx_init();
    map.win_ = mlx_new_window(map.mlx_, 1820, 1080, "CUB3D");
    map.img_.img = mlx_new_image(map.mlx_, 1820, 1080);
    map.img_.addr = mlx_get_data_addr(map.img_.img, &map.img_.bits_per_pixel, &map.img_.line_length, &map.img_.endian);
    mlx_loop(map.mlx_);
}