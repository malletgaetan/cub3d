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
		mlx_destroy_image(g_mlx_state.mlx, g_mlx_state.img);
	if (g_conf.so.img != NULL)
		mlx_destroy_image(g_mlx_state.mlx, g_mlx_state.img);
	if (g_conf.we.img != NULL)
		mlx_destroy_image(g_mlx_state.mlx, g_mlx_state.img);
	if (g_conf.no.img != NULL)
		mlx_destroy_image(g_mlx_state.mlx, g_mlx_state.img);
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

int	main(int argc, char **argv)
{
	gc_init(&(g_gc));
	if (argc != 2)
		return (0);
	g_mlx_state.mlx = mlx_init();
	if (g_mlx_state.mlx == NULL)
		return (1);
	if (parser(argv[1]))
	{
		unsetup_mlx();
		gc_clean(&(g_gc));
		return (1);
	}
	if (setup_mlx())
	{
		unsetup_mlx();
		gc_clean(&(g_gc));
		return (1);
	}
	g_gs.pos_x = 3;
	g_gs.pos_y = 3;
	g_gs.dir_x = -1;
	g_gs.dir_y = 0;
	g_gs.plane_x = 0;
	g_gs.plane_y = 0.66;
	mlx_loop(g_mlx_state.mlx);
	unsetup_mlx();
	gc_clean(&(g_gc));
	return (0);
}
