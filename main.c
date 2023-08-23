#include "cub.h"
void	my_mlx_pixel_put(t_immg *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	dda_line(t_cub	*data, double x, double y, int color)
{
	t_dda	dda;
	dda.dx = x - data->player.x;
	dda.dy = y - data->player.y;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.steps = fabs(dda.dx);
	else
		dda.steps = fabs(dda.dy);
	dda.xinc = dda.dx / dda.steps;
	dda.yinc = dda.dy / dda.steps;
	dda.xi = data->player.x;
	dda.yi = data->player.y;
	while((int)dda.steps--)
	{
		my_mlx_pixel_put(&data->img_, dda.xi, dda.yi, color);
		dda.xi += dda.xinc;
		// if ((dda.xi / 64))
		dda.yi += dda.yinc;
	}
}

void	draw_player(t_cub *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < SIZE / 3)
	{
		j = 0;
		while (j < SIZE / 3)
		{
			my_mlx_pixel_put(&data->img_, x + i, y + j, color);
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

double rad(double ang)
{
	return (ang * (PI / 180));
}

int	check_if_hitwall(t_cub *data, float x, float y)
{
	if(data->map[(int)(x/ SQRS)]  && data->map[(int)(x/ SQRS)][(int)(y / SQRS)] == '1')
		return (1);
	return (0);
}

double	count_distance(t_cub *data, double x,  double y)
{
	double distance = 0;

	distance = sqrt(pow(data->player.x - x, 2) + pow(data->player.y - y, 2));
	return (distance);
}


int	keey_hook(int key, t_cub *data)
{
	if (key == 65307)
		exit(0);
	data->player.xtmp = data->player.x;
	data->player.ytmp = data->player.y;
	if (key == 119)
		move_up(data);
	else if (key == 115)
		move_down(data);
	else if (key == 97)
		move_left(data);
	else if (key == 100)
		move_right(data);
	else if (key == 65361)
		leftrotation(data);
	else if (key == 65363)
		rightrotation(data);
	if (data->map[(int)data->player.ytmp / SQRS][(int)data->player.xtmp / SQRS] != '1')
	{
		data->player.x = data->player.xtmp;
		data->player.y = data->player.ytmp;
		data->img_.img = mlx_new_image(data->mlx_, WIDTH, HEIGHT);
		data->img_.addr = mlx_get_data_addr(data->img_.img, &data->img_.bits_per_pixel,
		&data->img_.line_length, &data->img_.endian);
		drow_2d(data);
		mlx_put_image_to_window(data->mlx_, data->win_, data->img_.img, 0, 0);
	}
	return (0);
}

int main(int ac, char **av)
 {
	(void)ac;
	t_cub   data;
	// t_pars *list;
	// list = NULL;
	
	// create_list(&list, av[1]);
	// data.map = get_map(list);

    t_pars *list;
    t_path *path;

	list = NULL;
	create_list(&list, av[1]);
	data.map = get_map(list);
	check_characters(data.map);
	ifvalid_floor(data.map);
	if (!is_mapclosed(data.map))
	{
		write(2, "error map not closed\n", 21);
		exit (1);
	}
	ifvalid_space(data.map);
	path__(list, &path);
	rgbtoint(path);
	data.map = rectagle_map(data.map);
	// for(int a = 0; data.map[a]; a++)
	// {
	// 	printf("%s\n", data.map[a]);
	// }
	// exit (1);
	////
	data.mlx_ = mlx_init();
	data.win_ = mlx_new_window(data.mlx_, WIDTH , HEIGHT, "Abomination3D");
	data.img_.img = mlx_new_image(data.mlx_, WIDTH, HEIGHT);
	data.img_.addr = mlx_get_data_addr(data.img_.img, &data.img_.bits_per_pixel,
		&data.img_.line_length, &data.img_.endian);
	player_position(&data);
	drow_2d(&data);
	mlx_put_image_to_window(data.mlx_, data.win_, data.img_.img, 0, 0);
	mlx_hook(data.win_, 2, 1L<<0, keey_hook, &data);
	mlx_loop(data.mlx_);
}
