#include "cub.h"
#include <mlx.h>
 
int main(int ac, char **av)
{
    t_cub   map;

    map.mlx_ = mlx_init();
    map.win_ = mlx_new_window(map.mlx_, 1820, 500, "CUB3D");
    mlx_loop(map.mlx_);
}