/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yahamdan <yahamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 10:31:24 by yahamdan          #+#    #+#             */
/*   Updated: 2023/09/03 18:26:39 by yahamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_position(double pos, int tex_width)
{
	int	position;

	position = ((pos / SQRS) - (int)(pos / SQRS)) * tex_width;
	return (position);
}

void	hor_init(t_cub *data, t_help *cub, double hdist, double pdist)
{
	cub->pphight = (SQRS / hdist) * pdist;
	cub->y = (HEIGHT / 2) - (cub->pphight / 2);
	cub->y_top = cub->y;
	cub->y_down = (HEIGHT / 2) + (cub->pphight / 2);
	cub->size = data->xpm[0].img_height / cub->pphight;
}

void	rander_floor(t_cub *data, int i, int x)
{
	int	color;

	while (i < HEIGHT)
	{
		color = data->path->f;
		my_mlx_pixel_put(&data->img_, x, i, color);
		i++;
	}
}

int	get_horcolor(t_cub *data, double hight, double *hitwall)
{
	int	color;

	if (sin(data->rayangle) > 0)
		color = get_pixels(&data->xpm[2], \
			get_position(hitwall[0], data->xpm[2].img_width), hight);
	else
		color = get_pixels(&data->xpm[3], \
			get_position(hitwall[0], data->xpm[3].img_width), hight);
	return (color);
}

void	ver_init(t_cub *data, t_help *cub, double vdist, double pdist)
{
	cub->pphight = (SQRS / vdist) * pdist;
	cub->y = (HEIGHT / 2) - (cub->pphight / 2);
	cub->y_top = cub->y;
	cub->y_down = (HEIGHT / 2) + (cub->pphight / 2);
	cub->size = data->xpm[0].img_height / cub->pphight;
}

int	get_vercolor(t_cub *data, double hight, double *hitwall)
{
	int	color;

	if (cos(data->rayangle) > 0)
		color = get_pixels(&data->xpm[0], \
			get_position(hitwall[1], data->xpm[0].img_width), hight);
	else
		color = get_pixels(&data->xpm[1], \
			get_position(hitwall[1], data->xpm[1].img_width), hight);
	return (color);
}

int	get_color_weapon(t_weapon *weapom, int x, int y)
{
	char	*dst;

	if (x >= 0 && x < weapom->img_width && y >= 0 && y < weapom->img_height)
	{
		dst = weapom->data_img + (y * weapom->size_line + x
				* (weapom->bits_per_pixel / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}
