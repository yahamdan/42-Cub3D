
#include "../cub.h"


int	get_position(double pos, int tex_width)
{
	int	position;
	// int  px = tex_width /( (int)pos % tex_width);
	position = ((pos / SQRS) - (int)(pos / SQRS)) * tex_width;
	// printf("%d\n", position);
	// printf("x ==== %d\n", px);
	// position = x1 * tex_width;
	// position = (int)pos % tex_width;
	// printf("pos ======= %f,,,, hei === %f\n pos final = %f\n", pos, height_wall, px);
	return (position);
}

void	horizontal_rayrander(t_cub *data, double hordist, double *horhitwall, double PPDistance, int x)
{
	double	PPhight;
	double	y;
	double	hight = 0.0;
	int color;
	double size;
	int		i = 0;
	
	hordist *= cos(data->player.rotation - data->rayangle);
	PPhight = (SQRS / hordist) * PPDistance;
	y = (HEIGHT / 2) - (PPhight / 2);
	int y_top = y;
	int y_down = (HEIGHT / 2) + (PPhight / 2);
	size = data->xpm[0].img_height / PPhight;
	while (i < y)
	{
		color = 0x45adff;
		my_mlx_pixel_put(&data->img_, x, i, color);
		i++;
	}
	i = y_top;
	while(i < y_down)
	{
		if(sin(data->rayangle) > 0)
			color = get_pixels(&data->xpm[2],get_position(horhitwall[0], data->xpm[2].img_width), hight);
		else
			color = get_pixels(&data->xpm[3],get_position(horhitwall[0], data->xpm[3].img_width), hight);
		my_mlx_pixel_put(&data->img_, x, i, color);
		if (i > HEIGHT)
			break;
		hight += size;
		i++;
	}
	while(i < HEIGHT)
	{
		color = 0x758189;
		my_mlx_pixel_put(&data->img_, x, i, color);
		i++;
	}
}

void	vertical_rayrander(t_cub *data, double verdist, double *verhitwall, double PPDistance, int x)
{
	double	PPhight;
	double	y;
	double	hight = 0.0;
	int color;
	double size;
	int		i = 0;

	verdist *= cos(data->player.rotation - data->rayangle);
	PPhight = (SQRS / verdist) * PPDistance;
	y = (HEIGHT / 2) - (PPhight / 2);
	int y_top = y;
	int y_down = (HEIGHT / 2) + (PPhight / 2);
	size = data->xpm[0].img_height / PPhight;
	while (i < y)
	{
		color = 0x45adff;
		my_mlx_pixel_put(&data->img_, x, i, color);
		i++;
	}
	i = y_top;
	while(i < y_down)
	{
		if(cos(data->rayangle) > 0)
			color = get_pixels(&data->xpm[0],get_position(verhitwall[1], data->xpm[0].img_width), hight);
		else
			color = get_pixels(&data->xpm[1],get_position(verhitwall[1], data->xpm[1].img_width), hight);
		
		my_mlx_pixel_put(&data->img_, x, i, color);
		if (i > HEIGHT)
			break;
		hight += size;
		i++;
	}
	while(i < HEIGHT)
	{
		color = 0x758189;
		my_mlx_pixel_put(&data->img_, x, i, color);
		i++;
	}
}


void	ray_caster(t_cub *data, int x)
{
	double	*verhitwall;
	double	*horhitwall;
	double	PPDistance;
	double	PPhight;
	double	verdist;
	double	hordist;
	double	y;
	double size;
	int		i = 0;
	double	hight = 0.0;
	int color;
	int o = 0;
	horhitwall = horizontal_check(data);
	verhitwall =  vertical_check(data);
	verdist = count_distance(data, verhitwall[0], verhitwall[1]);
	hordist = count_distance(data, horhitwall[0], horhitwall[1]);
	PPDistance = (WIDTH / 2) / tan(rad(30));
	if (horhitwall[1] <= 0 || horhitwall[0] <=0)
		vertical_rayrander(data, verdist, verhitwall, PPDistance, x);
	else if (verhitwall[1] <= 0 || verhitwall[0] <= 0)
		horizontal_rayrander(data, hordist, horhitwall, PPDistance,x);
	else if (count_distance(data, horhitwall[0], horhitwall[1]) >= count_distance(data, verhitwall[0], verhitwall[1]))
		vertical_rayrander(data, verdist, verhitwall, PPDistance, x);
	else
		horizontal_rayrander(data, hordist, horhitwall, PPDistance, x);

	free(verhitwall);
	free(horhitwall);
}


int	get_color_weapon(t_weapon *weapom,int x, int y)
{

	char	*dst;
	if (x >= 0 && x < weapom->img_width && y >= 0 && y < weapom->img_height)
	{

		dst = weapom->data_img + (y * weapom->size_line + x
				* (weapom->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

void	draw_weapon(int x, t_weapon *weapon, t_cub *data)
{
	int top_weapon = HEIGHT /2.3;
	int y = 0;
	int h = 0;
	static int a = 0;
	unsigned int  color ;
	unsigned int tmp_color;
	while (y < weapon->img_height && a < weapon->img_width)
	{
		color = get_color_weapon(weapon, a, y);
		tmp_color = color;
		if ((tmp_color >> 24) == 0)
			my_mlx_pixel_put(&data->img_, x, top_weapon, color);
		// else
		// 	my_mlx_pixel_put(&data->img_, x, top_weapon, 0xff0000);
		top_weapon++;
		// a++;
		y++;
	}
	if (a == weapon->img_width)
		a= 0;
	a++;
	// while (top_weapon < HEIGHT)
	// {
		// printf("height ===== %d,,,,,, wi === %d ,,,,,, %d\n", HEIGHT, WIDTH, top_weapon);
		// mlx_put_image_to_window(data->mlx_, data->win_, data->->img, WIDTH /2.3, HEIGHT/1.26);
		// top_weapon++;
	// }
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
	// x = data->player, t_weapon *weapon.x , hight = data->player.y;
	int k = 0;
	data->rayangle = data->player.rotation - rad(30);
	while(k < CRNUM)
	{
		ray_caster(data, k);
		data->rayangle += FOV / CRNUM;
		k++;
	}
	drow_minimap(data);
}
