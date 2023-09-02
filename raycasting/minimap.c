#include "../cub.h"

void	drow_sqr(t_cub *data, float y, float x , int color)
{
	int i;
	int j;
	
	i = y - 10;
	while(i < y)
	{
		j = x - 10;
		while(j < x)
		{
			if (i == y - 1 || j == x -1)
				my_mlx_pixel_put(&data->img_, i, j, 0x000000);
			else 
				my_mlx_pixel_put(&data->img_, i, j, color);
			j++;
		}
		i++;
	}
}

void	drow_p(t_cub *data)
{
	int i;
	int j;
	
	i = 75;
	while (i < 78)
	{
		j = 75;
		while (j < 78)
		{
			my_mlx_pixel_put(&data->img_, i , j, 0xff00000);
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
	
	y_v = (data->player.y) / 8 - 75;
	j = -1;
	while (++j < 150)
	{
		i = 0;
		x_v = data->player.x / 8 - 75;
		while (i < 150)
		{
			if ((x_v / 8) < data->h_w.width && (x_v / 8) >= 0 && (y_v / 8) < data->h_w.height && (y_v /8) >= 0 && data->map[y_v / 8][x_v / 8] == '1')
				my_mlx_pixel_put(&data->img_, i , j, 0x000000);
			else
				my_mlx_pixel_put(&data->img_, i , j, 0xFFFFFF);
			x_v ++;
			i++;
		}
		y_v ++;
	}
	drow_p(data);
}