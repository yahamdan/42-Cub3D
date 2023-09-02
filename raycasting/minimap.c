#include "../cub.h"

void	drow_p(t_cub *data)
{
	int i;
	int j;
	
	i = 75;
	while (i < 79)
	{
		j = 50;
		while (j < 54)
		{
			my_mlx_pixel_put(&data->img_, i , j, 0x2e3787);
			j++;
		}
		i++;
	}
}

void	drow_minimap(t_cub *data)
{
	int i;
	int j;
	int x_v;
	int y_v;
	
	y_v = (data->player.y) / 8 - 50;
	j = 1;
	while (++j < 100)
	{
		i = 1;
		x_v = data->player.x / 8 - 75;
		while (++i < 150)
		{
			if (i == 149 || j == 99 || i == 2 || j == 2)
				my_mlx_pixel_put(&data->img_, i , j, 0x000000);
			else if ((x_v / 8) < data->h_w.width && (x_v / 8) >= 0 && (y_v / 8) < data->h_w.height && (y_v /8) >= 0 && data->map[y_v / 8][x_v / 8] == '1')
				my_mlx_pixel_put(&data->img_, i , j, 0x000000);
			else
				my_mlx_pixel_put(&data->img_, i , j, 0xBfbfbf);
			x_v ++;
		}
		y_v ++;
	}
	drow_p(data);
}
