/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:18:14 by tvalimak          #+#    #+#             */
/*   Updated: 2024/03/24 18:52:19 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/printf/include/ft_printf.h"
# include "../libft/printf/libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <fcntl.h>
# define WIDTH 1024
# define HEIGHT 1024
# define TILE_PX 32

typedef struct s_game
{
	mlx_t			*mlx;
	char			**map;
	char			**f_map;
	char			*map_temp;
	int				width;
	int				height;
	int				player_posx;
	int				player_posy;
	int				player_pos_found;
	int				moves;
	int				collectible;
	int				ex_count;
	char			*line;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*floor_texture;
	mlx_texture_t	*player_texture;
	mlx_texture_t	*colle_texture;
	mlx_texture_t	*exit_texture;
	mlx_image_t		*wall_images;
	mlx_image_t		*floor_images;
	mlx_image_t		*player_images;
	mlx_image_t		*colle_images;
	mlx_image_t		*exit_images;
}					t_game;

typedef struct s_sprites
{
	mlx_image_t		*grass;
	mlx_image_t		*wall;
	mlx_image_t		*mushroom;
	mlx_image_t		*door_open;
	mlx_image_t		*door_closed;
	mlx_image_t		*knight_idle;
}				t_sprites;

typedef struct s_map
{
	int				fd;
	int				map_width;
	int				map_height;
	bool			has_exit;
	bool			has_start;
	bool			has_player;
	bool			connected;
	int				player_x;
	int				player_y;
	int				start_x;
	int				start_y;
	int				exit_x;
	int				exit_y;
	int				moves;
	size_t			collectables;
	size_t			collected;
	char			**map_grid;
	t_sprites		*sprites;
	char			valids[6];
	t_game			*game;
	mlx_t			*mlx;
}				t_map;

t_sprites	*set_sprites_struct(mlx_t *mlx, t_map *map);
t_sprites	*load_grass_tile(mlx_t *mlx, t_sprites *sprites);
void		error(char *str, int flag);
void		fill_background(t_map *map);
void		map_rendering(t_map *map);
void		render_main(t_map *map);

#endif
