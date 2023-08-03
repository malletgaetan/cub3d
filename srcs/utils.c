#include "cub3d.h"

// rotation anti horaire
void	rotate_player(double radians)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g_gs.dir_x;
	g_gs.dir_x = (old_dir_x * cos(radians)) - (g_gs.dir_y * sin(radians));
	g_gs.dir_y = (old_dir_x * sin(radians)) + (g_gs.dir_y * cos(radians));
	old_plane_x = g_gs.plane_x;
	g_gs.plane_x = (old_plane_x * cos(radians)) - (g_gs.plane_y * sin(radians));
	g_gs.plane_y = (old_plane_x * sin(radians)) + (g_gs.plane_y * cos(radians));
}
