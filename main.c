#include "cub.h"
// #include <mlx.h>
 


int main(int ac, char **av)
{
     t_pars *list;
     char **map;

     list = NULL;
     create_list(&list, av[1]);
     map = get_map(list);
     check_characters(map);
     if (!is_mapclosed(map))
     {
          write(2, "error map not closed\n", 21);
     }
     // int i = 0;
	// while (map[i])
	// 	printf("%s\n", map[i++]);
}
// int main(int ac, char **av)
// {
//     t_cub   map;

//     map.mlx_ = mlx_init();
//     map.win_ = mlx_new_window(map.mlx_, 1820, 500, "CUB3D");
//     mlx_loop(map.mlx_);
// }