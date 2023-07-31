#ifndef CUB_H
#define CUB_H

#include <mlx.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_cub
{
    void    *mlx_;
    void    *win_;
}   t_cub;


typedef struct s_pars
{
    char *string;
	struct s_pars *next;
}              t_pars ;


#endif