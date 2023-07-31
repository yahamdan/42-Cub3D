#include "../cub.h"

void	create_list(t_pars **list, char *n_file)
{
	char *str;
	int fd;

	fd = open(n_file, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		ft_lstadd_back(list, ft_lstnew(str));
		str = get_next_line(fd);
	}
	while (*list)
	{
		printf("%s\n",  (*list)->string);
		(*list) = (*list)->next;
	}
}