#include "cub3d.h"

void	setup_dda(t_dda *data)
{
	data->delta_dist_x = (data->ray_dir_x == 0) ? 1e30 : fabs(1 / data->ray_dir_x);
	data->delta_dist_y = (data->ray_dir_y == 0) ? 1e30 : fabs(1 / data->ray_dir_y);
	data->hit = 0;
	if(data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (g_gs.pos_x - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 - g_gs.pos_x) * data->delta_dist_x;
	}
	if(data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (g_gs.pos_y - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 - g_gs.pos_y) * data->delta_dist_y;
	}
}

static t_texture	*step_x(t_dda *data)
{
	t_texture	*text;

	text = NULL;
	data->side_dist_x += data->delta_dist_x;
	data->map_x += data->step_x;
	data->side = 0;
	if (g_conf.map[data->map_x][data->map_y] != '0')
	{
			if (data->step_x > 0)
				text = &(g_conf.we);
			else
				text = &(g_conf.ea);
			data->hit = 1;
	}
	return (text);
}

static t_texture	*step_y(t_dda *data)
{
	t_texture	*text;

	text = NULL;
	data->side_dist_y += data->delta_dist_y;
	data->map_y += data->step_y;
	data->side = 1;
	if (g_conf.map[data->map_x][data->map_y] != '0')
	{
			if (data->step_y > 0)
				text = &(g_conf.so);
			else
				text = &(g_conf.no);
			data->hit = 1;
	}
	return (text);
}

t_texture	*dda(t_dda *data)
{
	t_texture	*text;

	while(data->hit == 0)
	{
		if(data->side_dist_x < data->side_dist_y)
			text = step_x(data);
		else
			text = step_y(data);
	}
	if(data->side == 0)
		data->wall_dist = (data->side_dist_x - data->delta_dist_x);
	else
		data->wall_dist = (data->side_dist_y - data->delta_dist_y);
	return (text);
}
