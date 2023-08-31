#include "../cub.h"

void	get_steps(t_cub *data)
{
	data->ver.xintercept = floor(data->player.x / SQRS) * SQRS;
	if(cos(data->rayangle) > 0)
		data->ver.xintercept += SQRS;
	data->ver.yintercept = (data->player.x - data->ver.xintercept) * tan(data->rayangle) ;
	if (sin(data->rayangle) < 0)
		data->ver.yintercept = data->player.y - fabs(data->ver.yintercept);
	else
		data->ver.yintercept = data->player.y + fabs(data->ver.yintercept);
	data->ver.xstep = SQRS;
	if (cos(data->rayangle) < 0)
		data->ver.xstep *= -1;
	data->ver.ystep = SQRS * tan(data->rayangle);
	if((sin(data->rayangle) > 0 && data->ver.ystep < 0)
		|| (sin(data->rayangle) < 0 && data->ver.ystep > 0))
		data->ver.ystep *= -1;
	data->ver.next_verx = data->ver.xintercept;
	data->ver.next_very = data->ver.yintercept;
	if(cos(data->rayangle) < 0)
		data->ver.next_verx -= 0.001;
}

double	*vertical_check(t_cub *data)
{
	double * hitwall;

	hitwall = malloc(2 * sizeof(double));
	get_steps(data);
	while(1)
	{
		if (data->ver.next_very >= (SQRS * 16) || data->ver.next_very <= 0
			|| data->ver.next_verx >= (SQRS * 34) || data->ver.next_verx <= 0)
		{
			hitwall[0] = -1;
			hitwall[1] = -1;
			break;
		}
		if (check_if_hitwall(data, (data->ver.next_very), (data->ver.next_verx)))
		{
			hitwall[0] = data->ver.next_verx;
			hitwall[1] = data->ver.next_very;
			break;
		}
		data->ver.next_verx += data->ver.xstep;
		data->ver.next_very += data->ver.ystep;
	}
	return(hitwall);
}
