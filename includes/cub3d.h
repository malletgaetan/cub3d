/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmallet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:29:02 by gmallet           #+#    #+#             */
/*   Updated: 2023/08/03 18:29:03 by gmallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "mlx.h"
# include "gc.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

typedef struct s_mlx_state
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_mlx_state;

typedef struct s_texture
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_conf
{
	char		**map;
	int			cell_color;
	int			floor_color;
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
}	t_conf;

typedef struct s_game_state
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_game_state;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
}	t_dda;

extern t_mlx_state	g_mlx_state;
extern t_gcan		g_gc;
extern t_game_state	g_gs;
extern t_conf		g_conf;

void		rotate_player(double radians);

// ENGINE
int			handle_keypress(int keysym, void *param);
int			engine_render(void *param);
void		img_pix_put(int x, int y, int color);
void		draw_vertical_line(int x, int lh, t_texture *t, int tx);
double		min(double a, double b);
double		max(double a, double b);
void		setup_dda(t_dda *data);
t_texture	*dda(t_dda *data);

// PARSER
void		recup_pos(void);
void		destroy_pos(char ***map);
void		rotate_player(double radians);
int			t_line(char *map);
int			ft_atoi(char *nptr);
int			map_filled(char **map);
int			map_error(char **map);
char		*ft_strjoin(char *s1, char *s2);
int			parser(char *arg);
void		recup_texture(char *txt, char *find, int x);
int			recup_color(char *txt, char find, int x);
int		recup_map(char *txt);
char		*ft_get_line(char *save);
char		*ft_save(char *save);
char		*ft_read_and_save(int fd, char *save);
char		*get_next_line(int fd);
size_t		ft_strlen(char *str);
char		*ft_strchr(char *s, int c);
int			is_character(char c);

#endif
