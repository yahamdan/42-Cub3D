
#include "../cub.h"

void	ray_caster(t_cub *data, int x)
{
	double	*verhitwall;
	double	*horhitwall;
	double	PPDistance;
	double	PPhight;
	double	verdist;
	double	hordist;
	double	y;
	int		i = 0;
	
	horhitwall = horizontal_check(data);
	verhitwall =  vertical_check(data);
	verdist = count_distance(data, verhitwall[0], verhitwall[1]);
	hordist = count_distance(data, horhitwall[0], horhitwall[1]);
	PPDistance = (WIDTH / 2) / tan(rad(30));
	if (horhitwall[1] < 0 || horhitwall[0] < 0)
	{
		verdist *= cos(data->player.rotation - data->rayangle);
		PPhight = (SQRS / verdist) * PPDistance;
		y = (HEIGHT / 2) - (PPhight / 2);
		
		while(i < PPhight)
		{
			my_mlx_pixel_put(&data->img_, x, y, 0x46FF33);
			y++;
			i++;
		}
		free(verhitwall);
		free(horhitwall);
		return ;
	}
	if (verhitwall[1] < 0 || verhitwall[0] < 0)
	{
		hordist *= cos(data->player.rotation - data->rayangle);
		PPhight = (SQRS / hordist) * PPDistance;
		y = (HEIGHT / 2) - (PPhight / 2);
		while(i < PPhight)
		{
			my_mlx_pixel_put(&data->img_, x, y, 0x2596be);
			y++;
			i++;
		}
		free(verhitwall);
		free(horhitwall);
		return ;
	}
	if (count_distance(data, horhitwall[0], horhitwall[1]) >= count_distance(data, verhitwall[0], verhitwall[1]))
	{
		verdist *= cos(data->player.rotation - data->rayangle);
		PPhight = (SQRS / verdist) * PPDistance;
		y = (HEIGHT / 2) - (PPhight / 2);
		while(i < PPhight)
		{
			my_mlx_pixel_put(&data->img_, x, y, 0x46FF33);
			y++;
			i++;
		}
	}
	else
	{
		hordist *= cos(data->player.rotation - data->rayangle);
		PPhight = (SQRS / hordist) * PPDistance;
		y = ( HEIGHT / 2) - (PPhight / 2);
		while(i < PPhight)
		{
			my_mlx_pixel_put(&data->img_, x, y, 0x2596be);
			y++;
			i++;
		}
	}
	free(verhitwall);
	free(horhitwall);
}

void	player_position(t_cub *data)
{
	int i = 0;
	int j;

	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if(data->map[i][j] == 'W')
			{
				data->player.x = (j * SQRS) + 32;
				data->player.y = (i * SQRS) + 32;
			}
			j++;
		}
		i++;
	}
	data->player.rotation = rad(180);
}

void    drow_2d(t_cub *data)
{
	// int i,j;
	// i = 0;
	// while(data->map[i])
	// {
	// 	j = 0;
	// 	while(data->map[i][j])

	// 	{
	// 		if (data->map[i][j] == '1')
	// 			drow_map(data, ((i + 1) * SQRS), ((j + 1) * SQRS), 0x2F2D2C);
	// 		else if (data->map[i][j] != '1' && data->map[i][j] != '\n' && data->map[i][j] != ' ')
	// 			drow_map(data, ((i + 1) * SQRS), ((j + 1) * SQRS), 0xB8AFAF);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// my_mlx_pixel_put(&data->img_, data->player.x, data->player.y, 0x0000FF);
	//draw_player(data, data->player.x, data->player.y, 0x0000FF);
	//dda_line(data, data->player.xintercept, data->player.yintercept);
	// double  x,y;
	// x = data->player.x , y = data->player.y;
	// while (data->map[(int)(y + 1) / SQRS][(int)(x + 1) / SQRS] != '1')
	// {
	// 	my_mlx_pixel_put(&data->img_ ,x,y, 0x0000FF);
	// 	x += cos(data->player.rotation);
	// 	y += sin(data->player.rotation);
	// }
	int k = 0;
	data->rayangle = data->player.rotation - rad(30);
	while(k < CRNUM)
	{
		ray_caster(data, k);
		data->rayangle += FOV / CRNUM;
		k++;
	}
}
