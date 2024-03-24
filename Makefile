CC = gcc
#CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CFLAGS = -g
SRCDIR = sources
OBJDIR = objects
LIBFTDIR = ./libft/printf/
GNLDIR	 = ./libft/get_next_line/
MLXDIR = MLX42
MLX42 = $(MLXDIR)/build/libmlx42.a
LIBFT = $(LIBFTDIR)/libft.a
PROGRAM = so_long
UNAME_S := $(shell uname -s)
PRINTF = ./libft/printf/libftprintf.a
GNL = ./libft/get_next_line/gnl.a

ifeq ($(UNAME_S),Linux)
LDFLAGS = -Iinclude -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
LDFLAGS = -Iinclude -I MLX42 -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
endif

SRCS = $(SRCDIR)/main.c $(SRCDIR)/structs_initialization.c $(SRCDIR)/rendering.c

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(PROGRAM)

$(PROGRAM): $(OBJS) $(PRINTF) $(GNL) $(MLX42)
	$(CC) $(CFLAGS) -o $@ $^ $(PRINTF) $(GNL) $(MLX42) $(LDFLAGS)

check_flags:
	@echo $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(MLX42):
	cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

$(PRINTF): $(LIBFT_SRC)
	$(MAKE) -C $(LIBFTDIR)
	$(MAKE) -C $(GNLDIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C ./libft/printf
	$(MAKE) clean -C ./libft/get_next_line/
	rm -rf $(MLXDIR)/build

fclean: clean
	rm -rf $(PROGRAM)
	$(MAKE) fclean -C ./libft/printf
	$(MAKE) fclean -C ./libft/get_next_line/

re: fclean all

.PHONY: all clean fclean re check_flags
