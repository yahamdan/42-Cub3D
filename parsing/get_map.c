#include "../cub.h"

void	firstandlast_line(char **map, int height)
{
	int	j;

	j = 0;
	//first line////
	while (map[0][j])
	{
		if (map[0][j] == ' ')
		{
			if ((map[0][j + 1] == '0' || map[0][j - 1] == '0' || map[1][j] == '0'))
			{
				write(2, "map not valid\n", 14);
				exit(1);
			}
		}
		j++;
	}
	///last line ///
	j = 0;
	while (map[height][j])
	{
		if (map[height][j] == ' ')
		{
			if (map[height][j + 1] == '0' || map[height][j - 1] == '0' || map[height - 1][j] == '0')
			{
				write(2, "map not valid\n", 14);
				exit(1);
			}
		}
		j++;
	}

}

void	ifvalid_floor(char **map)
{
	size_t	i;
	size_t	j;
	size_t	hight;

	i = 1;
	hight = 0;
	while (map[hight])
		hight++;
	hight--;
	while (map[i] && i < hight)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if ((i > 0 && (j >= ft_strlen(map[i - 1]) || j >= ft_strlen(map[i + 1]))))
				{
					write(2, "floor not valid\n", 16);
					exit(1);
				}
				else if ((j > 0 && map[i][j-1] == ' ') || map[i][j+1] == ' ' || map[i+1][j] == ' ' || map[i-1][j] == ' ')
				{
					write(2, "floor not valid\n", 16);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

// void	ifvalid_space(char **map)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	j = 0;
// 	while (map[len])
// 		len++;
// 	len--;
// 	firstandlast_line(map, len);
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (map[i][j] == ' ')
// 			{
// 				if (i >= 1 && i < len && (map[i][j + 1] == '0' || map[i][j - 1] == '0' || map[i + 1][j] == '0' || map[i - 1][j] == '0'))
// 				{
// 					write(2, "map not valid\n", 14);
// 					exit(1);
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

int	hieghtlen(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}


void	iscolorvalid(char	**color)
{
	int	i;
	int	j;

	i = 0;

	if (hieghtlen(color) > 3){
		write (2, "eroor in colors\n", 16);
		exit (1);
	}
	while (color[i])
	{
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j]))
			{
				write (2, "not digit\n", 10);
				exit (1);
			}
			j++;
		}
		i++;
	}
}

void	rang_color(int r, int g, int b)
{
	if (!(r >= 0 && r <= 255) || !(g >= 0 && g <= 255) || !(b >= 0 && b <= 255))
	{
		write (2, "invalid color\n", 13);
		exit (1);
	}
}

void	count_comma(char *path)
{
	int i;
	int	flag;

	i = 0;
	flag = 0;
	while (path[i])
	{
		if (path[i] == ',')
			flag++;
		i++;
	}
	if (flag >= 3)
	{
		write(2, "multiple comma\n", 15);
		exit(1);
	}
}

void	rgbtoint(t_path *path)
{
	int	i;
	char	**ceiling;
	char	**floor;

	i = 0;
	count_comma(path->C_path);
	count_comma(path->F_path);
	ceiling = ft_split(path->C_path, ',');
	floor = ft_split(path->F_path, ',');
	iscolorvalid(ceiling);
	iscolorvalid(floor);
	if (!ceiling[0] || !ceiling[1] || !ceiling[2] || !floor[0] || !floor[1] || !floor[2])
	{
		write (2, "invalid color\n", 14);
		exit (1);
	}
	else if (ft_strlen(ceiling[0]) > 3 || ft_strlen(ceiling[1]) > 3 || ft_strlen(ceiling[2]) > 3 ||
		ft_strlen(floor[0]) > 3 || ft_strlen(floor[1]) > 3 || ft_strlen(floor[2]) > 3)
	{
		write (2, "invalid color\n", 13);
		exit (1);
	}
	rang_color(ft_atoi(ceiling[0]), ft_atoi(ceiling[1]), ft_atoi(ceiling[2]));
	rang_color(ft_atoi(floor[0]), ft_atoi(floor[1]), ft_atoi(floor[2]));
	path->c = ft_atoi(ceiling[0]) * 65536 + ft_atoi(ceiling[1]) * 256 + ft_atoi(ceiling[2]);
	path->f = ft_atoi(floor[0]) * 65536 + ft_atoi(floor[1]) * 256 + ft_atoi(floor[2]);
}

char	*pathfind(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] == '/')
			return (ft_strdup(&str[i]));
		i++;
	}
	write(2, "invalid path\n", 13);
	exit(1);
	return (NULL);
}
char	*findrgb(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'C' || str[i] == 'F')
		{
			i += 2;
			return (ft_strdup(&str[i]));
		}
		i++;
	}
	return (NULL);
}

// void	path__(t_pars *list, t_path **path)
// {
// 	t_flag	flag;
// 	int		i;

// 	i = 0;
// 	flag.C = 0;
// 	flag.EA = 0;
// 	flag.F = 0;
// 	flag.NO = 0;
// 	flag.SO = 0;
// 	flag.WE = 0;
// 	*path = malloc(sizeof(t_path));
// 	while (list && list->string && list->string[0] != '1' && list->string[0] != '0' && list->string[0] != ' ')
// 	{
		
// 		if (list->string && list->string[0] != '\0')
// 			i++;
// 		if (!ft_strncmp(list->string, "NO ", 3))
// 		{
// 			if (flag.NO == 0)
// 				(*path)->NO_path = pathfind(list->string);
// 			else
// 			{
// 				write(2, "duplicate_\n", 10);
// 				exit(1);
// 			}
// 			flag.NO++;
// 		}
// 		else if (!ft_strncmp(list->string, "WE ", 3))
// 		{
// 			if (flag.WE == 0)
// 				(*path)->WE_path = pathfind(list->string);
// 			else
// 			{
// 				write(2, "duplicate\n", 10);
// 				exit(1);
// 			}
// 			flag.WE++;
// 		}
// 		else if (!ft_strncmp(list->string, "EA ", 3))
// 		{
// 			if (flag.EA == 0)
// 				(*path)->EA_path = pathfind(list->string);
// 			else
// 			{
// 				write(2, "duplicate\n", 10);
// 				exit(1);
// 			}
// 			flag.EA++;
// 		}
// 		else if (!ft_strncmp(list->string, "SO ", 3))
// 		{
// 			if (flag.SO == 0)
// 				(*path)->SO_path = pathfind(list->string);
// 			else
// 			{
// 				write(2, "duplicate\n", 10);
// 				exit(1);
// 			}
// 			flag.SO++;
// 		}
// 		else if (!ft_strncmp(list->string, "F ", 2))
// 		{
// 			if (flag.F == 0)
// 				(*path)->F_path = findrgb(list->string);
// 			else
// 			{
// 				write(2, "duplicate\n", 10);
// 				exit(1);
// 			}
// 			flag.F++;
// 		}
// 		else if (!ft_strncmp(list->string, "C ", 2))
// 		{
// 			if (flag.C == 0)
// 				(*path)->C_path = findrgb(list->string);
// 			else
// 			{
// 				write(2, "duplicate\n", 10);
// 				exit(1);
// 			}
// 			flag.C++;
// 		}
// 		list = list->next;
// 	}
// 	if (i != 6 || (flag.C == 0 || flag.EA == 0 || flag.F == 0 || flag.NO == 0 || flag.SO == 0 || flag.WE == 0))
// 	{
// 		write (2, "error\n", 6);
// 		exit (1);
// 	}
// }

char *switch_nline(char *str)
{
    int	i;

	i = 0;
    while (str && str[i])
	{
		if (str[i] == '\n')
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


char	**ignor_space(char **map)
{
	int	i;
	int j;
	int	x;

	i = 0;
	while (map[i] && map[i][0] != '\0')
	{
		j = 0;
		x = ft_strlen(map[i]) - 1;
		while(map[i][j] && map[i][j] == ' ')
		{
			map[i][j] = '1';
			j++;
		}
		while (map[i][x] && map[i][x] == ' ')
		{
			map[i][x] = '1';
			x--;
		}
		i++;
	}
	return (map);
}

int is_mapclosed(char **map)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	if (!map[i])
	{
		write(2, "ivalid map\n", 11);
		exit(1);
	}
	map = ignor_space(map);
	while (map[i])
		i++;
	i--;
	while (map[i] && map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (0);
		j++;
	}
	j = 0;
	while (map[0][j])
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
		{
			return (0);
		}
		j++;
	}
	i = 0;
	while (map[i])
	{
		if ((map[i] && !map[i][0]) || map[i][0] != '1' || map[i][ft_strlen(map[i])-1] != '1')
			return (0);
		i++;
	}
	return (1);
}

char	**get_map(t_pars *list)
{
	int		i;	
	char	**map;
	t_pars	*tmp;

	i = 0;
	while (list)
	{
		if (ft_strncmp(list->string, "NO ", 3) && ft_strncmp(list->string, "WE ", 3) 
			&& ft_strncmp(list->string, "EA ", 3) && ft_strncmp(list->string, "SO ", 3) 
				&& ft_strncmp(list->string, "F ", 2) && ft_strncmp(list->string, "C ", 2) && list->string && list->string[0] != '\0')
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
	if (fd == -1)
	{
		write(2, "open failed\n", 12);
		exit(1);
	}
	str = switch_nline(get_next_line(fd));
	while (str)
	{
		ft_lstadd_back(list, ft_lstnew(str));
		free(str);
		str = switch_nline(get_next_line(fd));
	}
	if (!*list)
	{
		write(2, "file .cub is empty\n", 19);
		exit(1);
	}	
}

int	height_map(char **map)
{
	int	i;

	i = 0;
	while(map[i])
		i++;
	i--;
	return (i);
}

void	check_characters(char **map)
{
	int i;
	int j;
	int	check;

	i = 0;
	check = 0;
	if (!map[0])
	{
		write(2, "need to setting map\n", 20);
		exit(1);
	}
	while (map[i] && i < height_map(map))
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i] && map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W')
			{
				write(2, "character not valid\n", 20);
				exit (1);
			}
			if (map[i] && (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W'))
			{
				if (j > 0 && i > 0 && (map[i + 1][j] == ' ' || map[i - 1][j] == ' '
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' '))
				{
					write (2, "there is space nearby player\n", 29);
					exit (1);
				}
				check++;
			}
			j++;
		}
		i++;
	}
	if (check != 1)
	{
		write(2, "more than player in map\n", 24);
		exit(1);
	}
}