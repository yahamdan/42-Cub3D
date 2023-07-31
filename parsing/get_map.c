#include "../cub.h"


int	check_ifvalid(t_pars *list)
{
	int	i;

	i = 0;
	while (list && i < 6)
	{
		if (ft_strncmp(list->string, "NO ", 3) && ft_strncmp(list->string, "WE ", 3) && ft_strncmp(list->string, "EA ", 3) 
			&& ft_strncmp(list->string, "SO ", 3) && ft_strncmp(list->string, "F ", 2) && ft_strncmp(list->string, "C ", 2))
				return (0);
		i++;	
		list = list->next;
	}
	return (1);
}


char	**get_map(t_pars *list)
{
	int	i;	
	char **map;
	t_pars *tmp;

	i = 0; 
	// if (!check_ifvalid(list))
	// {
	// 	write(2, "not valid\n", 10);
	// 	exit (1);
	// }
	while (list)
	{
		if (list->string[0] == '1' || list->string[0] == '0')
			break;
		list = list->next;
	}
	tmp = list;
	while (list)
	{
		i++;
		list = list->next;
	}
	map = malloc((sizeof(char *)* (i+1)));
	map[i] = NULL;
	i = 0;
	while (tmp)
	{
		map[i] = ft_strdup(tmp->string);
		i++;
		tmp = tmp->next;
	}
	i = 0;
	while (map[i])
		printf("%s\n", map[i++]);
	return (map);
}

void	create_list(t_pars **list, char *n_file)
{
	char *str = NULL;
	int fd;

	fd = open(n_file, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		ft_lstadd_back(list, ft_lstnew(str));
		free(str);
		str = get_next_line(fd);
	}
	// while (*list)
	// {
	// 	printf("%s\n",  (*list)->string);
	// 	(*list) = (*list)->next;
	// }
}
