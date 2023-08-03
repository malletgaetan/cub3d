NAME = cub3d
CC = gcc
INCLUDESDIR = includes/
SRCSDIR = srcs/
MLXDIR = minilibx-linux
LIBGCDIR = gc
MLX = libmlx.a
LIBGC = libgc.a
MLXFLAGS = -L $(MLXDIR) -l mlx -lXext -lX11 -lm
LIBGCFLAGS = -L $(LIBGCDIR) -l:$(LIBGC)
CFLAGS = -Wall -Werror -Wextra -g

SRCS=$(shell find $(SRCSDIR) -name '*.c')
OBJS=$(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(LIBGCDIR)/$(LIBGC):
	make -C $(LIBGCDIR)

$(MLXDIR)/$(MLX):
	make -C $(MLXDIR)

$(NAME): $(SRCS) $(MLXDIR)/$(MLX) $(LIBGCDIR)/$(LIBGC)
	$(CC) -o $(NAME) $(CFLAGS) -I $(INCLUDESDIR) $(SRCS) $(MLXFLAGS) $(LIBGCFLAGS)

fclean:
	rm -f $(NAME)
	make -C $(LIBGCDIR) fclean

clean:

re: clean fclean all
