/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werrahma <werrahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:00:58 by yahamdan          #+#    #+#             */
/*   Updated: 2023/09/03 21:23:16 by werrahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	my_mlx_pixel_put(t_immg *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}