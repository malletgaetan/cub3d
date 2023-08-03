#include "cub3d.h"

int	get_pix_color(t_texture *text, int x, int y)
{
	return (*(int *)(text->addr \
			+ (4 * text->width * y) \
			+ (4 * x)));
}

void	img_pix_put(int x, int y, int color)
{
	char	*dst;

	dst = g_mlx_state.img_addr + \
		(y * g_mlx_state.line_len + x * (g_mlx_state.bpp / 8));
	*(unsigned int *)dst = color;
}

void	set(int line_height, int *draw_start, int *draw_end)
{
	(*draw_start) = (-line_height / 2) + (SCREEN_HEIGHT / 2);
	if ((*draw_start) < 0)
		(*draw_start) = 0;
	if ((*draw_start) >= SCREEN_HEIGHT)
		(*draw_start) = SCREEN_HEIGHT - 1;
	(*draw_end) = (line_height / 2) + (SCREEN_HEIGHT / 2);
	if ((*draw_end) >= SCREEN_HEIGHT)
		(*draw_end) = SCREEN_HEIGHT - 1;
}

void	draw_vertical_line(int x, int line_height, t_texture *text, int text_x)
{
	int		y;
	int		draw_start;
	int		draw_end;
	double	step;
	double	text_y;

	set(line_height, &draw_start, &draw_end);
	y = 0;
	step = ((double)(text->height) / (double)(draw_end - draw_start));
	while (y < draw_start)
		img_pix_put(x, ++y, g_conf.cell_color);
	text_y = 0.0;
	while (y <= draw_end)
	{
		img_pix_put(x, y, get_pix_color(text, text_x, (int)text_y));
		text_y += step;
		++y;
	}
	while (y < SCREEN_HEIGHT)
		img_pix_put(x, ++y, g_conf.floor_color);
}
