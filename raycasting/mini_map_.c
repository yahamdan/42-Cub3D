
#include "../cub.h"

void	draw_player(t_cub *data, int x, int y, int color)
{
	x += 5;
	y += 5;
	my_mlx_pixel_put(&data->img_, x , y, color);
	// while (i < SIZE / 4)
	// {
	// 	j = 0;
	// 	while (j < SIZE / 4)
	// 	{
	// 		my_mlx_pixel_put(&data->img_, x + i , y + j, color);
	// 		my_mlx_pixel_put(&data->img_, x - i, y + j, color);
	// 		my_mlx_pixel_put(&data->img_, x + i, y - j, color);
	// 		my_mlx_pixel_put(&data->img_, x - i, y - j, color);
	// 		j++;
	// 	}
	// 	i++;
	// }
}

void	drow_map(t_cub *data, int i, int j , int color)
{
	int x;
	int y;
	x = 0;
	y = i - 10;
	while(y < 85)
	{
		x = j - 10;
		while(x < 120)
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
	//draw_player(data, (data->player.x - SQRS / 2) / SQRS * 10, (data->player.y - SQRS / 2) / SQRS *10, 0x0000FF);
}