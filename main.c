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

int	check_if_hitwall(t_cub *data, float x, float y)
{
	if(data->map[(int)(x/ SQRS)]  && data->map[(int)(x/ SQRS)][(int)(y / SQRS)] == '1')
		return (1);
	return (0);
}

int	keey_hook(int key, t_cub *data)
{
	data->player.xtmp = data->player.x;
	data->player.ytmp = data->player.y;
	if (key == 65307)
		exit(0);
	if (key == 119)
		move_up(data);
	if (key == 115)
		move_down(data);
	if (key == 97)
		move_left(data);
	if (key == 100)
		move_right(data);
	if (key == 65361)
		leftrotation(data);
	if (key == 65363)
		rightrotation(data);
	if (position_check(data, data->player.xtmp, data->player.ytmp))
	{
		data->player.x = data->player.xtmp;
		data->player.y = data->player.ytmp;
		mlx_render_img(data);
	}
	return (0);
}


int main(int ac, char **av)
 {
	t_cub	data;
	t_pars *list;

	list = NULL;
	ifvalid_mapname(ac , av[1]);
	create_list(&list, av[1]);
	data.map = get_map(list);
	path_checker(list, &data.path);
	ifvalid_floor(data.map);
	is_mapclosed(data.map);
	check_characters(data.map);
	rgbtoint(data.path);
	data.map = rectagle_map(data.map);
	h_w_map(data.map, &data.h_w);
	data.mlx_ = mlx_init();
	data.win_ = mlx_new_window(data.mlx_, WIDTH , HEIGHT, "Abomination3D");
	setting_texwalls(&data);
	player_position(&data);
	mlx_render_img(&data);
	mlx_hook(data.win_, 2, 1L<<0, keey_hook, &data);
	mlx_hook(data.win_, 6, 1L<<6 , mouse_hook, &data);
	mlx_hook(data.win_, 17, 0, event_hook, NULL);
	mlx_mouse_hide(data.mlx_, data.win_);
	mlx_loop(data.mlx_);
}
