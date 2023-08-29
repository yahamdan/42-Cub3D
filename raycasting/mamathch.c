
#include "../cub.h"

double rad(double ang)
{
	return (ang * (PI / 180));
}

double	count_distance(t_cub *data, double x, double y)
{
	double distance = 0;

	distance = sqrt(pow(data->player.x - x, 2) + pow(data->player.y - y, 2));
	return (distance);
}
