
#include "../cub.h"

int	check_if_hitwall(t_cub *data, float x, float y)
{
	if(data->map[(int)(x/ SQRS)]  && data->map[(int)(x/ SQRS)][(int)(y / SQRS)] == '1')
		return (1);
	return (0);
}

void	ray_caster(t_cub *data, int x)
{
	double	*verhitwall;
	double	*horhitwall;
	double	PPDistance;
	double	PPhight = 0;
	double	verdist;
	double	hordist;
	double	y = 0;
	int		i = 0;
	int color;
	
	horhitwall = horizontal_check(data);
	verhitwall =  vertical_check(data);
	verdist = count_distance(data, verhitwall[0], verhitwall[1]);
	hordist = count_distance(data, horhitwall[0], horhitwall[1]);
	PPDistance = (WIDTH / 2) / tan(rad(30));
	if (horhitwall[1] <= 0 || horhitwall[0] <= 0)
	{
		verdist *= cos(data->player.rotation - data->rayangle);
		PPhight = (SQRS / verdist) * PPDistance;
		y = (HEIGHT / 2) - (PPhight / 2);
		while(i < HEIGHT)
		{
			if(cos(data->rayangle) > 0)
				color = 0x527f81;
			else
				color = 0xCec26b;
			if (i < (HEIGHT /2 ) - (PPhight / 2))
				color = 0x45adff;
			else if (i > (HEIGHT /2 ) + (PPhight / 2))
				color = 0x758189;
			my_mlx_pixel_put(&data->img_, x, i, color);
			i++;
		};
		free(verhitwall);
		free(horhitwall);
		return ;
	}
	if (verhitwall[1] <= 0 || verhitwall[0] <= 0)
	{
		hordist *= cos(data->player.rotation - data->rayangle);
		PPhight = (SQRS / hordist) * PPDistance;
		y = (HEIGHT / 2) - (PPhight / 2);
		while(i < HEIGHT)
		{
			if(sin(data->rayangle) > 0)
				color = 0x1f4821;
			else
				color = 0x9e8d8b;
			if (i < (HEIGHT /2 ) - (PPhight / 2))
				color = 0x45adff;
			else if (i > (HEIGHT /2 ) + (PPhight / 2))
				color = 0x758189;
			my_mlx_pixel_put(&data->img_, x, i, color);
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
		while(i < HEIGHT)
		{
			if(cos(data->rayangle) > 0)
				color = 0x527f81;
			else
				color = 0xCec26b;
			if (i < (HEIGHT /2 ) - (PPhight / 2))
				color = 0x45adff;
			else if (i > (HEIGHT /2 ) + (PPhight / 2))
				color = 0x758189;
			my_mlx_pixel_put(&data->img_, x, i, color);
			y++;
			i++;
		}
	}
	else
	{
		hordist *= cos(data->player.rotation - data->rayangle);
		PPhight = (SQRS / hordist) * PPDistance;
		y = ( HEIGHT / 2) - (PPhight / 2);
		while(i < HEIGHT)
		{
			if(sin(data->rayangle) > 0)
				color = 0x1f4821;
			else
				color = 0x9e8d8b;
			if (i < (HEIGHT /2 ) - (PPhight / 2))
				color = 0x45adff;
			else if (i > (HEIGHT /2 ) + (PPhight / 2))
				color = 0x758189;
			my_mlx_pixel_put(&data->img_, x, i, color);
			y++;
			i++;
		}
	}
	free(verhitwall);
	free(horhitwall);
}

void	player_rotation(t_cub *data, int x, int y)
{
	if (data->map[x][y] == 'N')
		data->player.rotation = rad(270);
	else if (data->map[x][y] == 'S')
		data->player.rotation = rad(90);
	else if (data->map[x][y] == 'W')
		data->player.rotation = rad(180);
	else if (data->map[x][y] == 'E')
		data->player.rotation = 0;
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
			if(data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->player.x = (j * SQRS) + SQRS / 2;
				data->player.y = (i * SQRS) + SQRS /2;
				player_rotation(data, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
	data->mouse.x = 0;
	data->mouse.y = 0;
}
void draw_player_2d(t_cub *data)
{
	double	*verhitwall;
	double	*horhitwall;
	
	horhitwall = horizontal_check(data);
	verhitwall =  vertical_check(data);
	if (horhitwall[1] <= 0 || horhitwall[0] <= 0)
		dda_line(data, verhitwall[0], verhitwall[1], 0x46FF33);
	else if (verhitwall[1] <= 0 || verhitwall[0] <= 0)
		dda_line(data, horhitwall[0], horhitwall[1], 0x46FF33);
	if (count_distance(data, horhitwall[0], horhitwall[1]) >= count_distance(data, verhitwall[0], verhitwall[1]))
		 dda_line(data, verhitwall[0], verhitwall[1], 0x46FF33);
	else
		 dda_line(data, horhitwall[0], horhitwall[1], 0x46FF33);
}

void	minimap(t_cub *data)
{
	int i,j;
	i = 0;
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])

		{
			if (data->map[i][j] == '1')
				drow_map(data, ((i + 1) *  10), ((j + 1) *  10), 0x2F2D2C);
			else if (data->map[i][j] != '1' && data->map[i][j] != '\n' && data->map[i][j] != ' ')
				drow_map(data, ((i + 1) *  10), ((j + 1) *  10), 0xB8AFAF);
			j++;
		}
		i++;
	}
	//my_mlx_pixel_put(&data->img_, ((data->player.x / 64) - 32) * 10, ((data->player.y / 64) -32) * 10, 0x0000FF);
	draw_player(data, ((data->player.x / 64) - 32) * 10, ((data->player.y / 64) - 32) * 10, 0x0000FF);
}

void    drow_2d(t_cub *data)
{
	int i,j;
	i = 0;
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])

		{
			if (data->map[i][j] == '1')
				drow_map(data, ((i + 1) * SQRS), ((j + 1) * SQRS), 0x2F2D2C);
			else if (data->map[i][j] != '1' && data->map[i][j] != '\n' && data->map[i][j] != ' ')
				drow_map(data, ((i + 1) * SQRS), ((j + 1) * SQRS), 0xB8AFAF);
			j++;
		}
		i++;
	}
	my_mlx_pixel_put(&data->img_, data->player.x, data->player.y, 0x0000FF);

	draw_player(data, data->player.x, data->player.y, 0x0000FF);
	int k = 0;
	data->rayangle = data->player.rotation - rad(30);
	// //printf("here\n");
	while(k < CRNUM)
	{
		//ray_caster(data, k);
		draw_player_2d(data);
		data->rayangle += FOV / CRNUM;
		k++;
	}
	//minimap(data);
}
