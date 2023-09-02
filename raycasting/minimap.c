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

void	drow_p(t_cub *data, int x, int y)
{
	int i;
	int j;
	
	i = 0;
	while (i < SIZE / 4)
	{
		j = 0;
		while (j < SIZE / 4)
		{
			my_mlx_pixel_put(&data->img_, x + i, y + j, 0xff00000);
			my_mlx_pixel_put(&data->img_, x - i, y + j, 0xff00000);
			my_mlx_pixel_put(&data->img_, x + i, y - j, 0xff00000);
			my_mlx_pixel_put(&data->img_, x - i, y - j, 0xff00000);
			j++;
		}
		i++;
	}
}

void	drow_minimap(t_cub *data)
{
	float x_start;
	float y_start;
	float x_end;
	float y_end;
	
	float xx = (data->player.x) / 64;
	float yy = (data->player.y) / 64;
	float px;
	float py;
	
	x_start = xx - 10;
	y_start = yy - 5 ;
	x_end = xx + 10;
	y_end = yy + 5;
	if (x_start < 0)
	{
		x_end = 10 * 2;
		x_start = 0;
	}
	if (y_start < 0)
	{
		y_end = 5 * 2;
		y_start = 0;
	}
	if (x_end > data->h_w.width)
	{
		x_start = (data->h_w.width) - (10 * 2);
		x_end = data->h_w.width;
		if (x_start < 0)
			x_start = 0;
	}
	if (y_end > data->h_w.height)
	{
		y_start = (data->h_w.height) - (5 * 2);
		y_end = data->h_w.height;
		if(y_start < 0)
			y_start = 0;
	}
	int i = 1;
	int j;
	float x = x_start;
	while(y_start < y_end)
	{
		j = 1;
		x_start = x;
		while (x_start < x_end)
		{
			if (data->map[(int)y_start][(int)x_start] == '1')
				drow_sqr(data, j  * 10, i  * 10 ,0x2F2D2C);
			else if (data->map[(int)y_start][(int)x_start] == '0' || data->map[(int)y_start][(int)x_start] != '\n')
				drow_sqr(data, j * 10, i * 10, 0xB8AFAF);
			if (y_start == yy && x_start == xx)
			{
				px = j;
				py = i;
			}
			// else if (data->map[y_start][x_start] == 'N' || data->map[y_start][x_start] == 'W'
			// 	|| data->map[y_start][x_start] == 'E' || data->map[y_start][x_start] == 'S')
			// 		drow_sqr(data, j * 10, i * 10, 0xB8AFAF);
			j++;
			x_start ++;
		}
		i++;
		y_start++;
	}
	//float px = xx;
	//float py = yy;
	// if (px > 20)
	// 	px -= x_end;
	// if (px < 0)
	// 	px = 0;
	// if (py > 10)
		// py -= y_end;
	// if (py < 0)
	// 	py = 0;
	drow_p(data, px * 10, py * 10);
	//my_mlx_pixel_put(&data->img_, (px * 10) + 5, (py * 10) + 5, 0xff00000);
}