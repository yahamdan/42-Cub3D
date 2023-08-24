#include "../cub.h"

double	*vertical_check(t_cub *data)
{
	double * hitwall = malloc(2 * sizeof(double));
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
	while(1)
	{
		if (data->ver.next_very >= (32* 16) || data->ver.next_very <= 0
			|| data->ver.next_verx >= (32 * 33) || data->ver.next_verx <= 0)
		{
			data->ver.hitwallx = 0;
			data->ver.hitwally = 0;
			hitwall[0] = data->ver.hitwallx;
			hitwall[1] = data->ver.next_very;
			break;
		}
		if (check_if_hitwall(data, (data->ver.next_very), (data->ver.next_verx)))
		{
			data->ver.hitwallx = data->ver.next_verx;
			data->ver.hitwally = data->ver.next_very;
			hitwall[0] = data->ver.hitwallx;
			hitwall[1] = data->ver.next_very;
			break;
		}
		data->ver.next_verx += data->ver.xstep;
		data->ver.next_very += data->ver.ystep;
	}
	return(hitwall);
}