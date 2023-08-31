# include "../cub.h"

void	get_stepss(t_cub *data)
{
	data->hor.yintercept = floor((data->player.y / SQRS)) * SQRS;
	if (sin(data->rayangle) > 0)
		data->hor.yintercept += SQRS;
	data->hor.xintercept = ((data->player.y - data->hor.yintercept) / tan(data->rayangle));
	if (cos(data->rayangle) < 0)
		data->hor.xintercept = data->player.x - fabs(data->hor.xintercept);
	else
		data->hor.xintercept = data->player.x + fabs(data->hor.xintercept);
	data->hor.ystep = SQRS;
	if (sin(data->rayangle) < 0)
		data->hor.ystep *= -1;
	data->hor.xstep = SQRS / tan(data->rayangle);
	if ((cos(data->rayangle) < 0 && data->hor.xstep > 0)
		|| (cos(data->rayangle) > 0 && data->hor.xstep < 0))
	data->hor.xstep *= -1;
	data->hor.next_horx = data->hor.xintercept;
	data->hor.next_hory = data->hor.yintercept;
	if(sin(data->rayangle) < 0)
		data->hor.next_hory -= 0.001;
}

double	*horizontal_check(t_cub *data)
{
	double *horhitwall;

	horhitwall = malloc(2 * sizeof(double));
	get_stepss(data);
	while (1)
	{
		if (data->hor.next_horx >= (SQRS * 34) || data->hor.next_horx <= 0
			|| data->hor.next_hory >= (SQRS* 16) || data->hor.next_hory <= 0)
		{
			horhitwall[0] = -1;
			horhitwall[1] = -1;
			break;
		}
		if (check_if_hitwall(data, data->hor.next_hory, data->hor.next_horx))
		{
			horhitwall[0] = data->hor.next_horx;
			horhitwall[1] = data->hor.next_hory;
			break;
		}
		data->hor.next_horx += data->hor.xstep;
		data->hor.next_hory += data->hor.ystep;
	}
	return (horhitwall);
}
