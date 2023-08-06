#include "../cub.h"

char *switch_nline(char *str)
{
    int	i;

	i = 0;
    while (str && str[i])
	{
		if (str[i] == '\n' && str[0] != '\n')
			str[i] = '\0';
		i++;
	}
	return (str);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
int is_mapclosed(char **map)
{
	int	i;
	int j;
	char **map_splited;

	i = 0;
	j = 0;
	while (map[i])
		i++;
	i--;
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (0);
		j++;
	}
	j = 0;
	printf("%s\n", map[j]);
	while (map[0][j])
	{
		if (map[0][j] != '1' && map[i][j] != ' ')
		{
			printf("%c\n", map[0][j]);
			return (0);
		}
		j++;
	}
	return (1);
	i = 0;
	while (map[i])
	{
		map_splited = ft_split(map[i], '\n');
		if (map_splited[0][0] != '1' || map_splited[0][ft_strlen(map_splited[0])] != '1')
		{
			free_split(map_splited);
			return (0);
		}
		free_split(map_splited);
	}
	return (1);
		
}

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
	return (map);
}

void	create_list(t_pars **list, char *n_file)
{
	char *str = NULL;
	int fd;

	fd = open(n_file, O_RDONLY);
	str = switch_nline(get_next_line(fd));
	while (str)
	{
		ft_lstadd_back(list, ft_lstnew(str));
		free(str);
		str = switch_nline(get_next_line(fd));
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
	char	**map_splited;

	i = 0;
	while (map[i])
	{
		map_splited = ft_split(map[i], '\n');
		j = 0;
		// if (!is_mapclosed(map_splited))
		// 	return (0);
		while (map_splited[0][j])
		{
			if (map_splited[0][j] != ' ' && map_splited[0][j] != '1' && map_splited[0][j] != '0'
				&& map_splited[0][j] != 'N' && map_splited[0][j] != 'S' && map_splited[0][j] != 'E' && map_splited[0][j] != 'W')
			{
				printf("%c\n", map_splited[0][j]);
				free_split(map_splited);
				write(2, "character not valid\n", 20);
				return (0);
			}
			j++;
		}
		free_split(map_splited);
		i++;
	}
	return (1);
}