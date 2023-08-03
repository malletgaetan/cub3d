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

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

typedef struct s_mlx_state
{
	void		*mlx; // main job to set
	void		*win; // main job to set
	void		*img; // main job to set
	char		*img_addr; // main job to set
	int			bpp; // main job to set
	int			line_len; // main job to set
	int			endian; // main job to set
}	t_mlx_state;

typedef struct s_texture
{
	void	*img; // parser job to set
	int		width; // parser job to set
	int		height; // parser job to set
	char	*addr; // parser job to set
	int		bpp; // parser job to set
	int		line_len; // parser job to set
	int		endian; // parser job to set
}	t_texture;

typedef struct s_conf
{
	char		**map; // parser job to set
	int			cell_color; // parser job to set
	int			floor_color; // parser job to set
	t_texture	no; // parser job to set
	t_texture	so; // parser job to set
	t_texture	we; // parser job to set
	t_texture	ea; // parser job to set
	char		*north;
	char		*south;
	char		*east;
	char		*west;
}	t_conf;

typedef struct s_game_state
{
	double		pos_x; // parser job to set
	double		pos_y; // parser job to set
	double		dir_x; // parser job to set
	double		dir_y; // parser job to set
	double		plane_x; // engine job to set
	double		plane_y; // engine job to set
}	t_game_state;

typedef struct s_dda
{
	int		map_x; // engine job to set
	int		map_y; // engine job to set
	double	camera_x; // engine job to set
	double	ray_dir_x; // engine job to set
	double	ray_dir_y; // engine job to set
	double	side_dist_x; // engine job to set
	double	side_dist_y; // engine job to set
	int		step_x; // engine job to set
	int		step_y; // engine job to set
	int		hit; // engine job to set
	int		side; // engine job to set
	double	delta_dist_x; // engine job to set
	double	delta_dist_y; // engine job to set
	double	wall_dist; // engine job to set
}	t_dda;

extern t_mlx_state	g_mlx_state;
extern t_gcan	g_gc;
extern t_game_state	g_gs;
extern t_conf	g_conf;

// ENGINE
int			handle_keypress(int keysym, void *param);
int			engine_render(void *param);
void		img_pix_put(int x, int y, int color);
void		draw_vertical_line(int x, int line_height, t_texture *text, int text_x);
double		min(double a, double b);
double		max(double a, double b);
void		setup_dda(t_dda *data);
t_texture	*dda(t_dda *data);

// PARSER
void		recup_pos(void);
void		recup_orientation(void);
int			ft_atoi(char *nptr);
int			map_filled(char **map);
int			map_error(char **map);
char		*ft_strjoin(char *s1, char *s2);
int		parser(char *arg);
void		recup_texture(char *txt, char *find, int x);
int		recup_color(char *txt, char find, int x);
void		recup_map(char *txt);
char		*ft_get_line(char *save);
char		*ft_save(char *save);
char		*ft_read_and_save(int fd, char *save);
char		*get_next_line(int fd);
size_t		ft_strlen(char *str);
char		*ft_strchr(char *s, int c);
int		is_character(char c);

# endif
