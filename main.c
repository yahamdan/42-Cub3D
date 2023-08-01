#include "cub.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	//if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	//{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	//}
}
// #include <mlx.h>
 


// int main(int ac, char **av)
// {
//      t_pars *list;
//      char **map;

//      create_list(&list, av[1]);
//      map = get_map(list);
//      int i = 0;
// 	while (map[i])
// 		printf("%s\n", map[i++]);
// }
void    drow_2d(char **map, t_cub *data)
{
    int i = 0 , j = 0;
    int n;

                while(n++ > 64)
                    my_mlx_pixel_put(&data->img_, i, j, 0x785A54);
}

int main(int ac, char **av)
 {
     t_cub   ma;


    t_pars *list;
    char **map;
    
    create_list(&list, av[1]);
    map = get_map(list);
    ma.mlx_ = mlx_init();
    ma.win_ = mlx_new_window(ma.mlx_, 1820, 1080, "CUB3D");
    ma.img_.img = mlx_new_image(ma.mlx_, 1820, 1080);
    ma.img_.addr = mlx_get_data_addr(ma.img_.img, &ma.img_.bits_per_pixel, &ma.img_.line_length, &ma.img_.endian);
    drow_2d(map, &ma);
    mlx_loop(ma.mlx_);

}
//     map.mlx_ = mlx_init();
//     map.win_ = mlx_new_window(map.mlx_, 1820, 500, "CUB3D");
//     mlx_loop(map.mlx_);
// }
