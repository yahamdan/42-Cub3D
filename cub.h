#ifndef CUB_H
#define CUB_H

// #include <mlx.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "parsing/get_next_line.h"



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

void	create_list(t_pars **list, char *n_file);
void	ft_lstadd_back(t_pars **lst, t_pars *new);
t_pars	*ft_lstnew(char *str);
int	ft_strcmp(char *s1, char *s2);
char	**get_map(t_pars *list);
int	check_characters(char **map);
int is_mapclosed(char **map);

#endif