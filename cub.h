#ifndef CUB_H
#define CUB_H

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "parsing/get_next_line.h"

# define WIDTH (21 * 64)
# define HEIGHT (10 * 64)
# define SIZE 9

typedef struct s_dda
{
	double	dx;
	double	dy;
	double 	steps;
	double	xi;
	double	yi;
	double	xinc;
	double	yinc;
}		t_dda;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	double	xtmp;
	double	ytmp;
	double	x;
	double	y;
	double	rotation;
	double	xin;
	double	yin;
}	t_player;

typedef struct s_cub
{
	void    *mlx_;
	void    *win_;
	char	**map;
	struct s_img   img_;
	struct s_player player;
}   t_cub;

typedef struct s_pars
{
	char *string;
	struct s_pars *next;
}              t_pars ;

void	create_list(t_pars **list, char *n_file);
void	ft_lstadd_back(t_pars **lst, t_pars *new);
t_pars	*ft_lstnew(char *str);
int	ft_strcmp(char *s1, char *s2);
char	**get_map(t_pars *list);
int	check_characters(char **map);
int is_mapclosed(char **map);


// raycasting 
void    rightrotation(t_cub *data);
void    leftrotation(t_cub *data);
void    move_up(t_cub *data);
void    move_down(t_cub *data);
void    move_right(t_cub *data);
void    move_left(t_cub *data);

#endif