
#include "../cub.h"

void    mlx_render_img(t_cub *data)
{
	data->img_.img = mlx_new_image(data->mlx_, WIDTH, HEIGHT);
	data->img_.addr = mlx_get_data_addr(data->img_.img, &data->img_.bits_per_pixel,
	&data->img_.line_length, &data->img_.endian);
	drow_2d(data);
	mlx_put_image_to_window(data->mlx_, data->win_, data->img_.img, 0, 0);
}

int	position_check(t_cub *data, float newx, float newy)
{
	if (data->map[(int)(data->player.y / SQRS)][(int)(newx / SQRS)] != '1'
		&& data->map[(int)(newy / SQRS)][(int)(data->player.x / SQRS)] != '1'
		&& data->map[(int)(newy / SQRS)][(int)(newx / SQRS)] != '1')
			return (1);
	return (0);
}

int	keey_hook(int key, t_cub *data)
{
	data->player.xtmp = data->player.x;
	data->player.ytmp = data->player.y;
	if (key == 65307)
		exit(0);
	else if (key == 119)
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
	if (position_check(data, data->player.xtmp, data->player.ytmp))
	{
		data->player.x = data->player.xtmp;
		data->player.y = data->player.ytmp;
		mlx_render_img(data);
	}
	return (0);
}


int mouse_hook(int x, int y,t_cub *data)
{
	if (x >= WIDTH || x <= 0)
		mlx_mouse_move(data->mlx_, data->win_, WIDTH / 2, HEIGHT /2);
	if (x > data->mouse.x)
	{
		data->player.rotation += rad(1);
		if (data->player.rotation > 6.283185)
			data->player.rotation = 0;
	}
	else
	{
		data->player.rotation -= rad(1);
		if (data->player.rotation < 0)
			data->player.rotation = 6.283185;
	}
	data->mouse.x = x;
	data->mouse.y = y;
	mlx_render_img(data);
	return (0);
}