#ifndef CUB_H
#define CUB_H

#include <mlx.h>

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_cub
{
    void    *mlx_;
    void    *win_;
    t_img   img_;
}   t_cub;

#endif