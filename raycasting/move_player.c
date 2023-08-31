#include "../cub.h"

void	move_up(t_cub *data)
{
	data->player.xtmp += cos(data->player.rotation) * SPEED;
	data->player.ytmp += sin(data->player.rotation) * SPEED;
}
void	move_down(t_cub *data)
{
	data->player.xtmp += cos(data->player.rotation) * -SPEED;
	data->player.ytmp += sin(data->player.rotation) * -SPEED;
}

void	move_right(t_cub *data)
{
	data->player.xtmp += cos(data->player.rotation + rad(90)) * SPEED;
	data->player.ytmp += sin(data->player.rotation + rad(90)) * SPEED;
}

void	move_left(t_cub *data)
{
	data->player.xtmp += cos(data->player.rotation + rad(90)) * -SPEED;
	data->player.ytmp += sin(data->player.rotation + rad(90)) * -SPEED;
}
