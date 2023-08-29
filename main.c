#include "cub.h"

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




int main(int ac, char **av)
 {
	(void)ac;
	t_cub   data;
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
	player_position(&data);
	data.mlx_ = mlx_init();
	data.win_ = mlx_new_window(data.mlx_, WIDTH , HEIGHT, "Abomination3D");
	////////////////////////////////////////////////////////////////
	// data.weapon = malloc(sizeof(t_weapon) * 5);
	// data.weapon[0].relative_path = "./textures/gun/frame1.xpm";
	// data.weapon[1].relative_path = "./textures/gun/frame2.xpm";
	// data.weapon[2].relative_path = "./textures/gun/frame3.xpm";
	// data.weapon[3].relative_path = "./textures/gun/frame4.xpm";
	// data.weapon[4].relative_path = "./textures/gun/frame5.xpm";
	// data.weapon[0].img = mlx_xpm_file_to_image(data.mlx_, data.weapon[0].relative_path, &data.weapon[0].img_width, &data.weapon[0].img_height);
	// data.weapon[0].data_img =  (char *)mlx_get_data_addr(data.weapon[0].img, &data.weapon[0].bits_per_pixel, &data.weapon[0].size_line, &data.weapon[0].endian);
	// ///
	// 	data.weapon[1].img = mlx_xpm_file_to_image(data.mlx_, data.weapon[1].relative_path, &data.weapon[1].img_width, &data.weapon[1].img_height);
	// data.weapon[1].data_img =  (char *)mlx_get_data_addr(data.weapon[1].img, &data.weapon[1].bits_per_pixel, &data.weapon[1].size_line, &data.weapon[1].endian);
	// ///
	// 	data.weapon[2].img = mlx_xpm_file_to_image(data.mlx_, data.weapon[2].relative_path, &data.weapon[2].img_width, &data.weapon[2].img_height);
	// data.weapon[2].data_img =  (char *)mlx_get_data_addr(data.weapon[2].img, &data.weapon[2].bits_per_pixel, &data.weapon[2].size_line, &data.weapon[2].endian);
	// ///
	// 	data.weapon[3].img = mlx_xpm_file_to_image(data.mlx_, data.weapon[3].relative_path, &data.weapon[3].img_width, &data.weapon[3].img_height);
	// data.weapon[3].data_img =  (char *)mlx_get_data_addr(data.weapon[3].img, &data.weapon[3].bits_per_pixel, &data.weapon[3].size_line, &data.weapon[3].endian);
	// ///
	// 	data.weapon[4].img = mlx_xpm_file_to_image(data.mlx_, data.weapon[4].relative_path, &data.weapon[4].img_width, &data.weapon[4].img_height);
	// data.weapon[4].data_img =  (char *)mlx_get_data_addr(data.weapon[4].img, &data.weapon[4].bits_per_pixel, &data.weapon[4].size_line, &data.weapon[4].endian);
	// printf("%d\n", data.weapon.width);
	
	// weapon
	data.xpm = malloc(sizeof(t_xpm) * 4);
	data.xpm[0].relative_path = "./textures/marble/m1.xpm";
	data.xpm[1].relative_path = "./textures/map2/wall1.xpm";
	data.xpm[2].relative_path = "./textures/map2/wall2.xpm";
	data.xpm[3].relative_path = "./textures/marble/m2.xpm";
	data.xpm[0].img = mlx_xpm_file_to_image(data.mlx_, data.xpm[0].relative_path, &data.xpm[0].img_width, &data.xpm[0].img_height);
	data.xpm[1].img = mlx_xpm_file_to_image(data.mlx_, data.xpm[1].relative_path, &data.xpm[1].img_width, &data.xpm[1].img_height);
	data.xpm[2].img = mlx_xpm_file_to_image(data.mlx_, data.xpm[2].relative_path, &data.xpm[2].img_width, &data.xpm[2].img_height);
	data.xpm[3].img = mlx_xpm_file_to_image(data.mlx_, data.xpm[3].relative_path, &data.xpm[3].img_width, &data.xpm[3].img_height);
	// char *img = data.xpm.img;
	data.xpm[0].data_img = (char *)mlx_get_data_addr(data.xpm[0].img, &data.xpm[0].bits_per_pixel, &data.xpm[0].size_line, &data.xpm[0].endian);
	data.xpm[1].data_img = (char *)mlx_get_data_addr(data.xpm[1].img, &data.xpm[1].bits_per_pixel, &data.xpm[1].size_line, &data.xpm[1].endian);
	data.xpm[2].data_img = (char *)mlx_get_data_addr(data.xpm[2].img, &data.xpm[2].bits_per_pixel, &data.xpm[2].size_line, &data.xpm[2].endian);
	data.xpm[3].data_img = (char *)mlx_get_data_addr(data.xpm[3].img, &data.xpm[3].bits_per_pixel, &data.xpm[3].size_line, &data.xpm[3].endian);
	// printf("%s\n", data.xpm[0].data_img);
	////////////////////////////////////////////////////////////////
	mlx_render_img(&data);
	mlx_hook(data.win_, 2, 1L<<0, keey_hook, &data);
	mlx_hook(data.win_, 6, 1L<<6 , mouse_hook, &data);
	mlx_mouse_hide(data.mlx_, data.win_);
	mlx_loop(data.mlx_);
}
