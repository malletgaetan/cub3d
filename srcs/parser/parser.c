/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:49:33 by tbatteux          #+#    #+#             */
/*   Updated: 2023/08/03 16:09:17 by tbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*recup_txt(char *arg)
{
	int		fd;
	int		ret;
	char	*buf;
	char	*final;

	fd = open(arg, O_RDONLY);
	final = gc_malloc(&(g_gc), 1001 * sizeof(char));
	if (!final)
		return (NULL);
	buf = gc_malloc(&(g_gc), 1001 * sizeof(char));
	if (!buf)
	{
		free(final);
		return (NULL);
	}
	ret = read(fd, final, 1000);
	final[ret] = 0;
	while (ret > 0)
	{
		ret = read(fd, buf, 1000);
		buf[ret] = 0;
		final = ft_strjoin(final, buf);
	}
	return (final);
}

int	setup_textures(void)
{
	g_conf.no.img = mlx_xpm_file_to_image(g_mlx_state.mlx, \
		g_conf.north, &(g_conf.no.width), &(g_conf.no.height));
	if (g_conf.no.img == NULL)
		return (1);
	g_conf.no.addr = mlx_get_data_addr(g_conf.no.img, &(g_conf.no.bpp), \
		&(g_conf.no.line_len), &(g_conf.no.endian));
	g_conf.so.img = mlx_xpm_file_to_image(g_mlx_state.mlx, \
		g_conf.south, &(g_conf.so.width), &(g_conf.so.height));
	if (g_conf.so.img == NULL)
		return (1);
	g_conf.so.addr = mlx_get_data_addr(g_conf.no.img, &(g_conf.so.bpp), \
		&(g_conf.so.line_len), &(g_conf.so.endian));
	g_conf.we.img = mlx_xpm_file_to_image(g_mlx_state.mlx, \
		g_conf.west, &(g_conf.we.width), &(g_conf.we.height));
	if (g_conf.we.img == NULL)
		return (1);
	g_conf.we.addr = mlx_get_data_addr(g_conf.we.img, &(g_conf.we.bpp), \
		&(g_conf.we.line_len), &(g_conf.we.endian));
	g_conf.ea.img = mlx_xpm_file_to_image(g_mlx_state.mlx, \
		g_conf.east, &(g_conf.ea.width), &(g_conf.ea.height));
	if (g_conf.no.img == NULL)
		return (1);
	g_conf.ea.addr = mlx_get_data_addr(g_conf.ea.img, &(g_conf.ea.bpp), \
		&(g_conf.ea.line_len), &(g_conf.ea.endian));
	return (0);
}

int	parser(char *arg)
{
	char		*txt;

	txt = recup_txt(arg);
	recup_texture(txt, "NO", 1);
	recup_texture(txt, "SO", 2);
	recup_texture(txt, "WE", 3);
	recup_texture(txt, "EA", 4);
	if (setup_textures())
	{
		printf("Error: invalid textures\n");
		return (1);
	}
	if (recup_color(txt, 'C', 1) || recup_color(txt, 'F', 2))
		return (1);
	recup_map(txt);
	if (map_error(g_conf.map))
		return (1);
	recup_pos();
	recup_orientation();
	destroy_pos(&(g_conf.map));
	return (0);
}
