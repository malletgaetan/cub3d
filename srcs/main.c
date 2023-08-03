/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:26:55 by gmallet           #+#    #+#             */
/*   Updated: 2023/08/03 18:26:56 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_gcan			g_gc;
t_mlx_state		g_mlx_state;
t_game_state	g_gs;
t_conf			g_conf;

void	unsetup_mlx(void)
{
	if (g_mlx_state.img != NULL)
		mlx_destroy_image(g_mlx_state.mlx, g_mlx_state.img);
	if (g_conf.ea.img != NULL)
		mlx_destroy_image(g_mlx_state.mlx, g_conf.ea.img);
	if (g_conf.so.img != NULL)
		mlx_destroy_image(g_mlx_state.mlx, g_conf.so.img);
	if (g_conf.we.img != NULL)
		mlx_destroy_image(g_mlx_state.mlx, g_conf.we.img);
	if (g_conf.no.img != NULL)
		mlx_destroy_image(g_mlx_state.mlx, g_conf.no.img);
	if (g_mlx_state.mlx != NULL)
		mlx_destroy_display(g_mlx_state.mlx);
}

int	setup_mlx(void)
{
	g_mlx_state.win = mlx_new_window(g_mlx_state.mlx, \
		SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (g_mlx_state.win == NULL)
		return (1);
	g_mlx_state.img = mlx_new_image(g_mlx_state.mlx, \
		SCREEN_WIDTH, SCREEN_HEIGHT);
	if (g_mlx_state.img == NULL)
		return (1);
	g_mlx_state.img_addr = mlx_get_data_addr(g_mlx_state.img, \
			&(g_mlx_state.bpp), &(g_mlx_state.line_len), &(g_mlx_state.endian));
	mlx_hook(g_mlx_state.win, KeyPress, KeyPressMask, handle_keypress, NULL);
	mlx_hook(g_mlx_state.win, 17, 1L << 17, mlx_loop_end, g_mlx_state.mlx);
	mlx_expose_hook(g_mlx_state.win, engine_render, NULL);
	return (0);
}

void	quit(int err)
{
	unsetup_mlx();
	gc_clean(&(g_gc));
	exit(err);
}

int	main(int argc, char **argv)
{
	gc_init(&(g_gc));
	if (argc != 2)
		return (0);
	g_mlx_state.mlx = mlx_init();
	g_gs.dir_x = -1;
	g_gs.dir_y = 0;
	g_gs.plane_x = 0;
	g_gs.plane_y = 0.66;
	if (g_mlx_state.mlx == NULL)
		quit(1);
	if (parser(argv[1]))
		quit(1);
	if (setup_mlx())
		quit(1);
	mlx_loop(g_mlx_state.mlx);
	quit(0);
}
