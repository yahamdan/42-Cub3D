/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:17:13 by werrahma          #+#    #+#             */
/*   Updated: 2023/08/29 17:20:21 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	path_checker(t_pars *list, t_path **path)
{
	t_flag	flag;
	int		i;

	i = 0;
	flag.C = 0;
	flag.EA = 0;
	flag.F = 0;
	flag.NO = 0;
	flag.SO = 0;
	flag.WE = 0;
	*path = malloc(sizeof(t_path));
	while (list && list->string && list->string[0] != '1' && list->string[0] != '0' && list->string[0] != ' ')
	{
		
		if (list->string && list->string[0] != '\0')
			i++;
		if (!ft_strncmp(list->string, "NO ", 3))
		{
			if (flag.NO == 0)
				(*path)->NO_path = pathfind(list->string);
			else
			{
				write(2, "duplicate_\n", 10);
				exit(1);
			}
			flag.NO++;
		}
		else if (!ft_strncmp(list->string, "WE ", 3))
		{
			if (flag.WE == 0)
				(*path)->WE_path = pathfind(list->string);
			else
			{
				write(2, "duplicate\n", 10);
				exit(1);
			}
			flag.WE++;
		}
		else if (!ft_strncmp(list->string, "EA ", 3))
		{
			if (flag.EA == 0)
				(*path)->EA_path = pathfind(list->string);
			else
			{
				write(2, "duplicate\n", 10);
				exit(1);
			}
			flag.EA++;
		}
		else if (!ft_strncmp(list->string, "SO ", 3))
		{
			if (flag.SO == 0)
				(*path)->SO_path = pathfind(list->string);
			else
			{
				write(2, "duplicate\n", 10);
				exit(1);
			}
			flag.SO++;
		}
		else if (!ft_strncmp(list->string, "F ", 2))
		{
			if (flag.F == 0)
				(*path)->F_path = findrgb(list->string);
			else
			{
				write(2, "duplicate\n", 10);
				exit(1);
			}
			flag.F++;
		}
		else if (!ft_strncmp(list->string, "C ", 2))
		{
			if (flag.C == 0)
				(*path)->C_path = findrgb(list->string);
			else
			{
				write(2, "duplicate\n", 10);
				exit(1);
			}
			flag.C++;
		}
		list = list->next;
	}
	if (i != 6 || (flag.C == 0 || flag.EA == 0 || flag.F == 0 || flag.NO == 0 || flag.SO == 0 || flag.WE == 0))
	{
		write (2, "error\n", 6);
		exit (1);
	}
}