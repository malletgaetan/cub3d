/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:26:36 by gmallet           #+#    #+#             */
/*   Updated: 2023/08/03 18:26:37 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MS (double)0.5

static int	update_pos(double xadder, double yadder)
{
	if (g_conf.map[(int)(g_gs.pos_x + xadder)][(int)(g_gs.pos_y)] == '0')
		g_gs.pos_x += xadder;
	if (g_conf.map[(int)(g_gs.pos_x)][(int)(g_gs.pos_y + yadder)] == '0')
		g_gs.pos_y += yadder;
	return (0);
}

static int	player_movement(int keysym)
{
	if (keysym == XK_d)
		return (update_pos((g_gs.dir_y * MS), -(g_gs.dir_x * MS)));
	if (keysym == XK_a)
		return (update_pos(-(g_gs.dir_y * MS), (g_gs.dir_x * MS)));
	if (keysym == XK_w)
		return (update_pos((g_gs.dir_x * MS), (g_gs.dir_y * MS)));
	if (keysym == XK_s)
		return (update_pos(-(g_gs.dir_x * MS), -(g_gs.dir_y * MS)));
	return (1);
}

static int	player_vision(int keysym)
{
	double	angle;

	angle = 0;
	if (keysym == XK_Left)
		angle = 0.1;
	else if (keysym == XK_Right)
		angle = -0.1;
	if (angle == 0)
		return (1);
	rotate_player(angle);
	return (0);
}

int	handle_keypress(int keysym, void *param)
{
	(void)param;
	if (keysym == XK_Escape)
	{
		mlx_loop_end(g_mlx_state.mlx);
		return (0);
	}
	if (player_movement(keysym) && player_vision(keysym))
		return (0);
	engine_render(NULL);
	return (0);
}
