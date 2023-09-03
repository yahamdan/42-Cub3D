/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <yahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:31:34 by yahamdan          #+#    #+#             */
/*   Updated: 2023/09/03 14:42:39 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_if_hitwall(t_cub *data, float x, float y)
{
	if (data->map[(int)(x / SQRS)] &&
		data->map[(int)(x / SQRS)][(int)(y / SQRS)] == '1')
		return (1);
	return (0);
}

int	position_check(t_cub *d, float newx, float newy)
{
	if (d->map[(int)(newy - 10) / SQRS] && 
		d->map[(int)((d->player.y) / SQRS)][(int)((newx) / SQRS)] != '1'
		&& d->map[(int)((newy) / SQRS)][(int)((d->player.x) / SQRS)] != '1'
		&& d->map[(int)((newy - 10) / SQRS)][(int)((newx + 10) / SQRS)] != '1')
		return (1);
	return (0);
}
