#include "../cub.h"


int	if_dup(t_pars *list)
{
	t_pars *tmp;
	int		flag;

	tmp = list;
	flag = 0;
	while (list && list->string && list->string[0] != '1' && list->string[0] != '0')
	{
		if (!ft_strncmp(list->string, "NO ", 3) || !ft_strncmp(list->string, "WE ", 3) || !ft_strncmp(list->string, "EA ", 3) 
			|| !ft_strncmp(list->string, "SO ", 3) || !ft_strncmp(list->string, "F ", 2) || !ft_strncmp(list->string, "C ", 2))
			flag++;
		list = list->next;
	}
	if (flag > 6)
		return (0);
	return (1);
}

int	check_ifvalid(t_pars *list)
{
	int	i;
	int flag;

	i = 0;
	flag = 0;
	while (list && list->string[0] != '1' && list->string[0] != '0')
	{
		if (ft_strncmp(list->string, "NO ", 3) && ft_strncmp(list->string, "WE ", 3) && ft_strncmp(list->string, "EA ", 3) 
			&& ft_strncmp(list->string, "SO ", 3) && ft_strncmp(list->string, "F ", 2) && ft_strncmp(list->string, "C ", 2) && ft_strncmp(list->string, "\n", 2))
				return (0);
		else if (!if_dup(list))
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
	if (!check_ifvalid(list))
	{
		write(2, "not valid\n", 10);
		exit (1);
	}
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
int	check_characters(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W')
			{
				printf("%c\n", map[i][j]);
				write(2, "character not valid\n", 20);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}