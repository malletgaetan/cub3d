#include "cub3d.h"

char	map[7][6]=
{
		"111111",
		"100001",
		"100001",
		"100001",
		"100001",
		"100001",
		"111111",
};

int	get_color(t_dda *data)
{
	if (map[data->map_x][data->map_y] == 1)
		return (0x00FF0000);
	if (map[data->map_x][data->map_y] == 2)
		return (0x0000FF00);
	if (map[data->map_x][data->map_y] == 3)
		return (0x000000FF);
	else
		return (0x00FF00FF);
}

int engine_render(void *param)
{
	int			x;
	double		wall_x;
	t_dda		data;
	t_texture	*text;
	int			text_x;

	(void)param;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		data.camera_x = (2 * (x / (double)SCREEN_WIDTH)) - 1;
		data.ray_dir_x = g_gs.dir_x + g_gs.plane_x * data.camera_x;
		data.ray_dir_y = g_gs.dir_y + g_gs.plane_y * data.camera_x;
		data.map_x = (int)g_gs.pos_x;
		data.map_y = (int)g_gs.pos_y;
		setup_dda(&data);
		text = dda(&data);
		if (data.side == 0)
			wall_x = g_gs.pos_y + (data.wall_dist * data.ray_dir_y);
		else
			wall_x = g_gs.pos_x + (data.wall_dist * data.ray_dir_x);
		wall_x -= floor(wall_x);
		text_x = (int)(wall_x * (double)text->width);
		if ((data.side == 0) && (data.ray_dir_x > 0))
			text_x = text->width - text_x - 1;
		if ((data.side == 1) && (data.ray_dir_y < 0))
			text_x = text->width - text_x - 1;
		draw_vertical_line(x, (int)(SCREEN_HEIGHT / data.wall_dist), text, text_x);
		++x;
	}
	mlx_put_image_to_window(g_mlx_state.mlx, g_mlx_state.win,
		g_mlx_state.img, 0, 0);
	return (0);
}
