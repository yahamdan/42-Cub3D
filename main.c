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

void	dda_line(t_cub	*data, double x, double y)
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
	//double i = 0;
	//printf("%f\n", dda.steps);
	while((int)dda.steps--)
	{
		my_mlx_pixel_put(&data->img_, dda.xi, dda.yi, 0x000000FF);
		dda.xi += dda.xinc;
		dda.yi += dda.yinc;
	}
	//printf("%f.     %f\n", dda.xi, x);
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
	y = i - 64;
	while(y < i)
	{
		x = j - 64;
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

void    drow_2d(t_cub *data)
{
    t_pars *list;
    char **map;
	int i,j;
	i = 0;
	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == '1')
				drow_map(data, ((i + 1) *64), ((j + 1) * 64), 0x2F2D2C);
			else if (data->map[i][j] != '1' && data->map[i][j] != '\n')
				drow_map(data, ((i + 1) *64), ((j + 1) * 64), 0xB8AFAF);
			j++; 
		}
		i++;
	}
	my_mlx_pixel_put(&data->img_, data->player.x, data->player.y, 0x0000FF);
	draw_player(data, data->player.x, data->player.y, 0x0000FF);
	//dda_line(data, data->player.xin, data->player.yin);
	float x,y;
	x = data->player.x , y = data->player.y;
	for (int i = 0; i < 33 ; i++)
	{
		my_mlx_pixel_put(&data->img_ ,x,y, 0x0000FF);
		x += cos(data->player.rotation);
		y += sin(data->player.rotation);
	}
}
int	key_hook(int key, t_cub *data)
{
	printf("%f\n",  data->player.rotation);
	if (key == 53)
		exit(0);
	data->player.xtmp = data->player.x;
	data->player.ytmp = data->player.y;
	if (key == 13)
		move_up(data);
	else if (key == 1)
		move_down(data);
	else if (key == 0)
		move_left(data);
	else if (key == 2)
		move_right(data);
	else if (key == 123)
		leftrotation(data);
	else if (key == 124)
		rightrotation(data);
	if (data->map[(int)data->player.ytmp / 64][(int)data->player.xtmp / 64] != '1')
	{
		data->player.x = data->player.xtmp;
		data->player.y = data->player.ytmp;
		mlx_clear_window(data->mlx_, data->win_);
		data->player.xin = data->player.x + cos(data->player.rotation) * 35;
    	data->player.yin = data->player.y + sin(data->player.rotation) * 35;
		drow_2d(data);
		mlx_put_image_to_window(data->mlx_, data->win_, data->img_.img, 0, 0);
	}
	return (0);
	int i = 0;
	int j;

	while(data->map[i])
	{
		j = 0;
		while(data->map[i][j])
		{
			if(data->map[i][j] == 'P')
			{
				data->player.x = (j * 64) + 32;
				data->player.y = (i * 64) + 32;
			}
			j++;
		}
		i++;
	}
	data->player.rotation = 1.570796;
	data->player.xin =  data->player.x + cos(data->player.rotation) * 35;
    data->player.yin = data->player.y + sin(data->player.rotation) * 35;
}

int main(int ac, char **av)
 {
	t_cub   data;
	t_pars *list;
	list = NULL;
	
	create_list(&list, av[1]);
	data.map = get_map(list);
	data.mlx_ = mlx_init();
	data.win_ = mlx_new_window(data.mlx_, WIDTH , HEIGHT, "CUB3D");
	data.img_.img = mlx_new_image(data.mlx_, WIDTH, HEIGHT);
	data.img_.addr = mlx_get_data_addr(data.img_.img, &data.img_.bits_per_pixel,
		&data.img_.line_length, &data.img_.endian);
	player_position(&data);
	drow_2d(&data);
	mlx_put_image_to_window(data.mlx_, data.win_, data.img_.img, 0, 0);
	mlx_hook(data.win_, 02, 0, key_hook, &data);
	mlx_loop(data.mlx_);

}
