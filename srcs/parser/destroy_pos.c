/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:08:34 by tbatteux          #+#    #+#             */
/*   Updated: 2023/08/03 16:19:44 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	modif(int i, int j)
{
	if ((g_conf.map)[i][j] == 'N')
	{
		(g_conf.map)[i][j] = '0';
		rotate_player(M_PI / 2);
	}
	if ((g_conf.map)[i][j] == 'S')
	{
		(g_conf.map)[i][j] = '0';
		rotate_player(3 * M_PI / 2);
	}
	if ((g_conf.map)[i][j] == 'E')
	{
		(g_conf.map)[i][j] = '0';
		rotate_player(M_PI);
	}
	if ((g_conf.map)[i][j] == 'W')
	{
		(g_conf.map)[i][j] = '0';
		rotate_player(-M_PI);
	}
}

void	destroy_pos(void)
{
	int	i;
	int	j;

	i = 0;
	while((g_conf.map)[i])
	{
		j = 0;
		while ((g_conf.map)[i][j])
		{
			if (is_character((g_conf.map)[i][j]))
				modif(i, j);
			j++;
		}
		i++;
	}
}

