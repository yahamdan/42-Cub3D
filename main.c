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

////my_mlx_pixel_put2(&data->img_, &data->xpm,x, y);

int	get_pixels(t_xpm *xpm,int x, int y)
{

	char	*dst;
	// char	*dst1;
	// printf("%s\n", xpm->data_img);
	if (x >= 0 && x < xpm->img_width && y >= 0 && y < xpm->img_height)
	{

		dst = xpm->data_img + (y * xpm->size_line + x
				* (xpm->bits_per_pixel / 8));
		// // printf("%s\n", dst);
		// dst1 = data->addr + (y * data->line_length + x
		// 		* (data->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
		// *(unsigned int *)dst1 = *(unsigned int *)dst;
	}
	return (0);
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

void	setting_texweapons(t_cub *data)
{
	data->weapon = malloc(sizeof(t_weapon) * 5);
	data->weapon[0].relative_path = "./textures/gun/frame1.xpm";
	data->weapon[1].relative_path = "./textures/gun/frame2.xpm";
	data->weapon[2].relative_path = "./textures/gun/frame3.xpm";
	data->weapon[3].relative_path = "./textures/gun/frame4.xpm";
	data->weapon[4].relative_path = "./textures/gun/frame5.xpm";
	data->weapon[0].img = mlx_xpm_file_to_image(data->mlx_, data->weapon[0].relative_path, &data->weapon[0].img_width, &data->weapon[0].img_height);
	data->weapon[0].data_img =  (char *)mlx_get_data_addr(data->weapon[0].img, &data->weapon[0].bits_per_pixel, &data->weapon[0].size_line, &data->weapon[0].endian);
	///
	data->weapon[1].img = mlx_xpm_file_to_image(data->mlx_, data->weapon[1].relative_path, &data->weapon[1].img_width, &data->weapon[1].img_height);
	data->weapon[1].data_img =  (char *)mlx_get_data_addr(data->weapon[1].img, &data->weapon[1].bits_per_pixel, &data->weapon[1].size_line, &data->weapon[1].endian);
	///
	data->weapon[2].img = mlx_xpm_file_to_image(data->mlx_, data->weapon[2].relative_path, &data->weapon[2].img_width, &data->weapon[2].img_height);
	data->weapon[2].data_img =  (char *)mlx_get_data_addr(data->weapon[2].img, &data->weapon[2].bits_per_pixel, &data->weapon[2].size_line, &data->weapon[2].endian);
	///
		data->weapon[3].img = mlx_xpm_file_to_image(data->mlx_, data->weapon[3].relative_path, &data->weapon[3].img_width, &data->weapon[3].img_height);
	data->weapon[3].data_img =  (char *)mlx_get_data_addr(data->weapon[3].img, &data->weapon[3].bits_per_pixel, &data->weapon[3].size_line, &data->weapon[3].endian);
	///
	data->weapon[4].img = mlx_xpm_file_to_image(data->mlx_, data->weapon[4].relative_path, &data->weapon[4].img_width, &data->weapon[4].img_height);
	data->weapon[4].data_img =  (char *)mlx_get_data_addr(data->weapon[4].img, &data->weapon[4].bits_per_pixel, &data->weapon[4].size_line, &data->weapon[4].endian);
}


void	setting_texwalls(t_cub *data)
{
	int	i;

	i = 0;
	data->xpm = malloc(sizeof(t_xpm) * 4);
	data->xpm[0].relative_path = "./textures/map1/flag.xpm";
	data->xpm[1].relative_path = "./textures/map1/wall.xpm";
	data->xpm[2].relative_path = "./textures/map2/wall2.xpm";
	data->xpm[3].relative_path = "./textures/map1/svastika_tmp.xpm";
	data->xpm[0].img = mlx_xpm_file_to_image(data->mlx_, data->xpm[0].relative_path, &data->xpm[0].img_width, &data->xpm[0].img_height);
	data->xpm[1].img = mlx_xpm_file_to_image(data->mlx_, data->xpm[1].relative_path, &data->xpm[1].img_width, &data->xpm[1].img_height);
	data->xpm[2].img = mlx_xpm_file_to_image(data->mlx_, data->xpm[2].relative_path, &data->xpm[2].img_width, &data->xpm[2].img_height);
	data->xpm[3].img = mlx_xpm_file_to_image(data->mlx_, data->xpm[3].relative_path, &data->xpm[3].img_width, &data->xpm[3].img_height);
	while (i < 4)
	{
		if (!data->xpm[i].img)
		{
			write(2, "invalid texture\n", 15);
			exit(1);
		}
		i++;
	}
	data->xpm[0].data_img = (char *)mlx_get_data_addr(data->xpm[0].img, &data->xpm[0].bits_per_pixel, &data->xpm[0].size_line, &data->xpm[0].endian);
	data->xpm[1].data_img = (char *)mlx_get_data_addr(data->xpm[1].img, &data->xpm[1].bits_per_pixel, &data->xpm[1].size_line, &data->xpm[1].endian);
	data->xpm[2].data_img = (char *)mlx_get_data_addr(data->xpm[2].img, &data->xpm[2].bits_per_pixel, &data->xpm[2].size_line, &data->xpm[2].endian);
	data->xpm[3].data_img = (char *)mlx_get_data_addr(data->xpm[3].img, &data->xpm[3].bits_per_pixel, &data->xpm[3].size_line, &data->xpm[3].endian);
}

void	h_w_map(char **map, t_h_w *h_w)
{

	h_w->height = 0;
	h_w->width = 0;
	while(map[h_w->height])
		h_w->height++;
	h_w->width = ft_strlen(map[0]);
}

void	ifvalid_mapname(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '.')
		i++;
	if (ft_strcmp(&av[i], ".cub"))
	{
		write(2, "invalid name map\n", 17);
		exit(1);
	}
}

int main(int ac, char **av)
 {
	(void)ac;
	t_cub   data;
	t_weapon weapon;

    t_pars *list;
    // t_path *path;

	list = NULL;
	ifvalid_mapname(av[1]);
	create_list(&list, av[1]);
	data.map = get_map(list);
	path_checker(list, &data.path);
	ifvalid_floor(data.map);
	is_mapclosed(data.map);
	check_characters(data.map);
	rgbtoint(data.path);
	data.map = rectagle_map(data.map);
	h_w_map(data.map, &data.h_w); //// that's function is return a struct of height and width of map;
	// exit (1);
	data.mlx_ = mlx_init();
	data.win_ = mlx_new_window(data.mlx_, WIDTH , HEIGHT, "Abomination3D");
	// setting_texweapons(&data);
	setting_texwalls(&data);
	player_position(&data);
	mlx_render_img(&data);
	mlx_hook(data.win_, 2, 1L<<0, keey_hook, &data);
	mlx_hook(data.win_, 6, 1L<<6 , mouse_hook, &data);
	mlx_hook(data.win_, 17, 0, event_hook, NULL);
	mlx_mouse_hide(data.mlx_, data.win_);
	mlx_loop(data.mlx_);
}
