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
	// printf("%f      %f     %f\n", x, y, data->player.rotation);
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
	y = i - SQRTS;
	while(y < i)
	{
		x = j - SQRTS;
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

int	check_if_horhitwall(t_cub *data, float x, float y)
{
	if(data->map[(int)(x/ 64)][(int)(y / 64)] == '1')
		return (1);
	return (0);
}

int	check_if_verhitwall(t_cub *data, float x, float y)
{
	if (data->map[(int)(x/64)] && data->map[(int)(x/ 64)][(int)(y / 64)] == '1')
		return (1);
	return (0);
}

double	*horizontal_check(t_cub *data)
{

	double *horhitwall = malloc(2 * sizeof(double));
	data->hor.yintercept = floor((data->player.y / SQRTS)) * SQRTS;
	if (sin(data->rayangle) > 0)
		data->hor.yintercept += SQRTS;
	data->hor.xintercept = ((data->player.y - data->hor.yintercept) / tan(data->rayangle));
	if (cos(data->rayangle) < 0)
		data->hor.xintercept = data->player.x - fabs(data->hor.xintercept);
	else
		data->hor.xintercept = data->player.x + fabs(data->hor.xintercept);
	data->hor.ystep = SQRTS;
	if (sin(data->rayangle) < 0)
		data->hor.ystep *= -1;
	data->hor.xstep = SQRTS / tan(data->rayangle);
	if ((cos(data->rayangle) < 0 && data->hor.xstep > 0)
		|| (cos(data->rayangle) > 0 && data->hor.xstep < 0))
		data->hor.xstep *= -1;
	printf("{%f     %f}\n", data->hor.xstep, data->hor.ystep);
		
	data->hor.next_horx = data->hor.xintercept;
	data->hor.next_hory = data->hor.yintercept;
	if(sin(data->rayangle) < 0)
		data->hor.next_hory -= 0.001;
	while (data->hor.next_horx >= 0 && data->hor.next_horx <= WIDTH && data->hor.next_hory >= 0 && data->hor.next_hory <= HEIGHT)
	{
		if (check_if_horhitwall(data, data->hor.next_hory, data->hor.next_horx))
		{
			data->hor.hitwallx = data->hor.next_horx;
			data->hor.hitwally = data->hor.next_hory;
			horhitwall[0] = data->hor.hitwallx;
			horhitwall[1] = data->hor.hitwally;
			break;
		}
		data->hor.next_horx += data->hor.xstep;
		data->hor.next_hory += data->hor.ystep;
	}
	return (horhitwall);
}

double	*vertical_check(t_cub *data)
{
	double * hitwall = malloc(2 * sizeof(double));
	data->ver.xintercept = floor(data->player.x / SQRTS) * SQRTS;
	if(cos(data->rayangle) > 0)
		data->ver.xintercept += SQRTS;
	data->ver.yintercept = (data->player.x - data->ver.xintercept) * tan(data->rayangle) ;
	if (sin(data->rayangle) < 0)
		data->ver.yintercept = data->player.y - fabs(data->ver.yintercept);
	else
		data->ver.yintercept = data->player.y + fabs(data->ver.yintercept);
	data->ver.xstep = SQRTS;
	if (cos(data->rayangle) < 0)
		data->ver.xstep *= -1;
	data->ver.ystep = SQRTS * tan(data->rayangle);
	if((sin(data->rayangle) > 0 && data->ver.ystep < 0)
		|| (sin(data->rayangle) < 0 && data->ver.ystep > 0))
		data->ver.ystep *= -1;

	data->ver.next_verx = data->ver.xintercept;
	data->ver.next_very = data->ver.yintercept;
	if(cos(data->rayangle) < 0)
		data->ver.next_verx -= 0.001;
	while(data->ver.next_verx >= 0 && data->ver.next_verx <= WIDTH && data->ver.next_very >= 0 && data->ver.next_very <= HEIGHT)
	{
		if (check_if_verhitwall(data, (data->ver.next_very), (data->ver.next_verx)))
		{
			data->ver.hitwallx = data->ver.next_verx;
			data->ver.hitwally = data->ver.next_very;
			hitwall[0] = data->ver.hitwallx;
			hitwall[1] = data->ver.next_very;
			break;
		}
		data->ver.next_verx += data->ver.xstep;
		data->ver.next_very += data->ver.ystep;
	}
	return(hitwall);
}

double	count_distance(t_cub *data, double x,  double y)
{
	double distance;

	distance = sqrt(pow(data->player.x - x, 2) + pow(data->player.y - y, 2));

	return (distance);
}
void	ray_caster(t_cub *data)
{
	double *verhitwall;
	double *horhitwall;

	horhitwall = horizontal_check(data);
	verhitwall =  vertical_check(data);
	if (horhitwall[1] < 0 || horhitwall[0] < 0)
	{
		dda_line(data, verhitwall[0], verhitwall[1], 0x46FF33);
		return ;
	}
	if (verhitwall[1] < 0 || verhitwall[0] < 0)
	{
		dda_line(data, horhitwall[0], horhitwall[1], 0x000000FF);
		return ;
	}
	printf("vertical = %f   horizental == %f\n",  count_distance(data, verhitwall[0], verhitwall[1]), count_distance(data, horhitwall[0], horhitwall[1]));
	if (count_distance(data, horhitwall[0], horhitwall[1]) >= count_distance(data, verhitwall[0], verhitwall[1]))
		dda_line(data, verhitwall[0], verhitwall[1], 0x46FF33);
	else
		dda_line(data, horhitwall[0], horhitwall[1], 0x000000FF);
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
				drow_map(data, ((i + 1) * SQRTS), ((j + 1) * SQRTS), 0x2F2D2C);
			else if (data->map[i][j] != '1' && data->map[i][j] != '\n' && data->map[i][j] != ' ')
				drow_map(data, ((i + 1) * SQRTS), ((j + 1) * SQRTS), 0xB8AFAF);
			j++;
		}
		i++;
	}
	my_mlx_pixel_put(&data->img_, data->player.x, data->player.y, 0x0000FF);
	//draw_player(data, data->player.x, data->player.y, 0x0000FF);
	//dda_line(data, data->player.xintercept, data->player.yintercept);
	// double  x,y;
	// x = data->player.x , y = data->player.y;
	// while (data->map[(int)(y + 1) / SQRTS][(int)(x + 1) / SQRTS] != '1')
	// {
	// 	my_mlx_pixel_put(&data->img_ ,x,y, 0x0000FF);
	// 	x += cos(data->player.rotation);
	// 	y += sin(data->player.rotation);
	// }
	int k = 0;
	data->rayangle = data->player.rotation - rad(30);
	while(k < CRNUM)
	{
		ray_caster(data);
		data->rayangle += FOV / CRNUM;
		k++;
	}

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
	if (data->map[(int)data->player.ytmp / SQRTS][(int)data->player.xtmp / SQRTS] != '1')
	{
		data->player.x = data->player.xtmp;
		data->player.y = data->player.ytmp;
		mlx_clear_window(data->mlx_, data->win_);
		// data->player.xintercept = data->player.x + cos(data->player.rotation);
    	// data->player.yintercept = data->player.y + sin(data->player.rotation);
		drow_2d(data);
		mlx_put_image_to_window(data->mlx_, data->win_, data->img_.img, 0, 0);
	}
	return (0);
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
			if(data->map[i][j] == 'P')
			{
				data->player.x = (j * SQRTS) + 32;
				data->player.y = (i * SQRTS) + 32;
				// data->player.x = WIDTH / 2;
				// data->player.y = HEIGHT /2;
			}
			j++;
		}
		i++;
	}
	data->player.rotation = rad(90);
	// data->player.xintercept =  data->player.x + cos(data->player.rotation) * 32;
   	// data->player.yintercept = data->player.y + sin(data->player.rotation) * 32;
}

int main(int ac, char **av)
 {
	(void)ac;
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
	mlx_hook(data.win_, 2, 1L<<0, keey_hook, &data);
	mlx_loop(data.mlx_);
}
