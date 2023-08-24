
#include "../cub.h"

void	draw_player(t_cub *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SIZE / 4)
	{
		j = 0;
		while (j < SIZE / 4)
		{
			my_mlx_pixel_put(&data->img_, x + i , y + j, color);
			my_mlx_pixel_put(&data->img_, x - i, y + j, color);
			my_mlx_pixel_put(&data->img_, x + i, y - j, color);
			my_mlx_pixel_put(&data->img_, x - i, y - j, color);
			j++;
		}
		i++;
	}
}

void	drow_map(t_cub *data, int i, int j , int color)
{
	int x;
	int y;
	x = 0;
	y = i - SQRS;
	while(y < i)
	{
		x = j - SQRS;
		while(x < j)
		{
			if (x == j - 1)
				my_mlx_pixel_put(&data->img_, x, y, 0x17202A);
			else if (y == i - 1)
				my_mlx_pixel_put(&data->img_, x, y, 0x17202A);
			else
				my_mlx_pixel_put(&data->img_, x, y, color);
			x++;
		}
		y++;
	}
}