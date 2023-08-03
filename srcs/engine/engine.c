/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:26:09 by gmallet           #+#    #+#             */
/*   Updated: 2023/08/03 18:26:10 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_line(t_dda *data, int x)
{
	double		wall_x;
	t_texture	*text;
	int			text_x;

	text = dda(data);
	if (data->side == 0)
		wall_x = g_gs.pos_y + (data->wall_dist * data->ray_dir_y);
	else
		wall_x = g_gs.pos_x + (data->wall_dist * data->ray_dir_x);
	wall_x -= floor(wall_x);
	text_x = (int)(wall_x * (double)text->width);
	if ((data->side == 0) && (data->ray_dir_x > 0))
		text_x = text->width - text_x - 1;
	if ((data->side == 1) && (data->ray_dir_y < 0))
		text_x = text->width - text_x - 1;
	draw_vertical_line(x, (int)(SCREEN_HEIGHT / data->wall_dist), text, text_x);
}

int	engine_render(void *param)
{
	int			x;
	t_dda		data;

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
		render_line(&data, x++);
	}
	mlx_put_image_to_window(g_mlx_state.mlx, g_mlx_state.win,
		g_mlx_state.img, 0, 0);
	return (0);
}
