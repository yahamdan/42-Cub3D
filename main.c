#include "cub.h"


// void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
// {
//      t_pars *list;
//      char **map;

//      list = NULL;
//      create_list(&list, av[1]);
//      map = get_map(list);
//      check_characters(map);
//      if (!is_mapclosed(map))
//      {
//           write(2, "error map not closed\n", 21);
//      }
//      // int i = 0;
// 	// while (map[i])
// 	// 	printf("%s\n", map[i++]);
// 	char	*dst;

// 	//if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 	//{
// 		dst = data->addr + (y * data->line_length + x
// 				* (data->bits_per_pixel / 8));
// 		*(unsigned int *)dst = color;
// 	//}
// }
 


int main(int ac, char **av)
{
    t_pars *list;
    char **map;

	list = NULL;
	create_list(&list, av[1]);
	map = get_map(list);
     int i = 0;
	while (map[i])
		printf("%s***", map[i++]);
}
// void	drow(t_cub *data, int i, int j , int color)
// {
// 	int x;
// 	int y;
// 	x = i - 64;
// 	while(x < i - 1)
// 	{
// 		y = j - 64;
// 		while(y < j - 1)
// 		{
// 			my_mlx_pixel_put(&data->img_, y, x, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

// void    drow_2d(char **map, t_cub *data)
// {
// 	int i, j;

// 	i = 0;
// 	while(map[i])
// 	{
// 		j = 0;
// 		while(map[i][j])
// 		{
// 			if (map[i][j] == '1')
// 				drow(data, ((i + 1) *64), ((j + 1) * 64), 0x2F2D2C);
// 			else if (map[i][j] != '1' && map[i][j] != '\n')
// 				drow(data, ((i + 1) *64), ((j + 1) * 64), 0x785A54);
// 			j++; 
// 		}
// 		i++;
// 	}	
// }

// int main(int ac, char **av)
//  {
// 	 t_cub   ma;


// 	t_pars *list;
// 	list = NULL;
// 	char **map;
	
// 	create_list(&list, av[1]);
// 	map = get_map(list);
// 	ma.mlx_ = mlx_init();
// 	ma.win_ = mlx_new_window(ma.mlx_, (25 * 64), (10 * 64), "CUB3D");
// 	ma.img_.img = mlx_new_image(ma.mlx_, (25 * 64), (10 * 64));
// 	ma.img_.addr = mlx_get_data_addr(ma.img_.img, &ma.img_.bits_per_pixel, &ma.img_.line_length, &ma.img_.endian);
// 	drow_2d(map, &ma);
// 	mlx_put_image_to_window(ma.mlx_, ma.win_, ma.img_.img, 0, 0);
// 	mlx_loop(ma.mlx_);

// }
