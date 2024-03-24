/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:26:36 by tvalimak          #+#    #+#             */
/*   Updated: 2024/03/24 18:51:55 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

#define TILE_PX 32

void	error(char *str, int flag)
{
	if (flag == 0)
	{
		ft_printf("Error\n");
		ft_printf("%s\n", str);
		exit(EXIT_FAILURE);
	}
}

static void	validate_helper(char *line, t_map *map)
{
	int		i;

	i = 0;
	if (*line == '\n' && i == 0)
		error("INVALID MAP", 0);
	while (map->valids[i])
	{
		while (i < 5 && *line != '\0')
		{
			if (*line == map->valids[i])
			{
				line++;
				i = -1;
			}
			i++;
		}
		if ((*line == '\0' || *line == '\n'))
			return ;
		else
			error("FORBIDDEN SYMBOLS IN MAP", 0);
	}
}

static void	validate_map(int fd, t_map *map)
{
	char	*line;
	char	*buffer;
	char	*temp_buffer;
	char	**result;

	line = get_next_line(fd);
	if (!line || line[0] == '\n')
	{
		free (line);
		error("EMPTY MAP FILE", 0);
	}
	buffer = ft_calloc(1, 1);
	if (!buffer)
		return ;
	validate_helper(line, map);
	while (line)
	{
		buffer = ft_strjoin(buffer, line);
		free (line);
		line = get_next_line(fd);
	}
	map->map_grid = ft_split(buffer, '\n');
	free (line);
	free (buffer);
	close (fd);
}

static void	validate_collectables(t_map *map)
{
	int	x;
	int	y;

	x = -1;
	while (++x < map->map_height)
	{
		y = -1;
		while (++y < map->map_width)
		{
			if (map->map_grid[x][y] == 'C')
				map->collectables += 1;
		}
	}
	if (map->collectables == 0)
		error("NO COLLECTABLE", 0);
	return ;
}

static void	set_starting_pos(int y, int x, t_map *map)
{
	if (map->has_start == true)
		error("DUPLICATE STARTING POSITIONS", 0);
	map->has_start = true;
	map->start_x = x;
	map->start_y = y;
}

static void	set_exit_pos(int y, int x, t_map *map)
{
	if (map->has_exit == true)
		error("DUPLICATE EXIT", 0);
	map->has_exit = true;
	map->exit_x = x;
	map->exit_y = y;
}

static void	validate_elements(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->map_height)
	{
		x = -1;
		while (++x < map->map_width)
		{
			if (map->map_grid[y][x] == 'P')
				set_starting_pos(y, x, map);
			if (map->map_grid[y][x] == 'E')
				set_exit_pos(y, x, map);
		}
	}
	validate_collectables(map);
	return ;
}

static void	validate_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->map_height)
	{
		if (map->map_grid[i][0] != '1' || \
			map->map_grid[i][map->map_width - 1] != '1')
			error("MAP NOT SURROUNDED BY WALLS", 0);
		i++;
	}
	i = 0;
	while (i < map->map_width)
	{
		if (map->map_grid[0][i] != '1' || \
			map->map_grid[map->map_height - 1][i] != '1')
			error("MAP NOT SURROUNDED BY WALLS", 0);
		i++;
	}
}

static void validate_widths(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 1;
	line = get_next_line(fd);
	map->map_width = ft_strlen(line) - 1;
	free (line);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free (line);
			break ;
		}
		if (ft_strlen(line) != map->map_width + 1)
		{
			error("MAP NOT RECTANGULAR OR EXCESSIVE NEWLINES AFTER MAP", 0);
			close (fd);
		}
		free (line);
		i++;
	}
	map->map_height = i;
	close (fd);
}

static int flood_fill(t_map *temp, size_t y, size_t x)
{
	if (temp->map_grid[y][x] == '1')
		return (0);
	if (temp->map_grid[y][x] == 'C')
		temp->collectables--;
	if (temp->map_grid[y][x] == 'E')
	{
		temp->connected = true;
		return (0);
	}
	temp->map_grid[y][x] = '1';
	if (flood_fill(temp, y - 1, x))
		return (1);
	if (flood_fill(temp, y, x - 1))
		return (1);
	if (flood_fill(temp, y + 1, x))
		return (1);
	if (flood_fill(temp, y, x + 1))
		return (1);
	return (0);
}

static void	free_grid(char **grid, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(grid[i]);
		grid[i] = NULL;
		i++;
	}
	free(grid);
	grid = NULL;
}

static void validate_path(t_map *map, int i)
{
	t_map	temp;

	temp.map_width = map->map_width;
	temp.map_height = map->map_height;
	temp.start_x = map->start_x;
	temp.start_y = map->start_y;
	temp.exit_x = map->exit_x;
	temp.exit_y = map->exit_y;
	temp.collectables = map->collectables;
	temp.map_grid = (char **)malloc(temp.map_height * sizeof(char *));
	if (!temp.map_grid)
		error ("TEMP MAP CREATION FAILED", 0);
	while (i < temp.map_height)
	{
		temp.map_grid[i] = ft_strdup(map->map_grid[i]);
		i++;
	}
	flood_fill(&temp, temp.start_y, temp.start_x);
	if (!(temp.collectables == 0 && temp.connected == true))
	{
		error ("NO VALID PATH IN MAP", 0);
		free_grid(temp.map_grid, temp.map_height);
	}
	free_grid(temp.map_grid, temp.map_height);
}

static void	validate_file(char *argv, t_map *map)
{
	char	*tmp;
	char	*line;

	tmp = ft_strnstr(argv, ".ber", ft_strlen(argv));
	if (tmp == NULL)
		error("INVALID FILETYPE", 0);
	if (ft_strlen(tmp) > 4)
		error("INVALID FILENAME", 0);
	map->fd = open(argv, O_RDONLY);
	if (map->fd < 0)
		error("FILE CANT BE OPENED", 0);
	validate_widths(map->fd, map);
	if (map->map_width > 32)
		error("MAP TOO WIDE", 0);
	if (map->map_height > 32)
		error("MAP TOO TALL", 0);
	map->fd = open(argv, O_RDONLY);
	validate_map(map->fd, map);
	validate_walls(map);
	validate_elements(map);
	validate_path(map, 0);
	return ;
}

void	fill_background(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (x < map->map_width)
		{
			if (mlx_image_to_window(map->mlx, map->sprites->grass, \
							x * TILE_PX, y * TILE_PX) < 0)
				error ("Failed to render grass sprite to screen", 0);
			x++;
		}
		y++;
	}
}

bool	collision_check(t_map *map, int y, int x)
{
	if (map->map_grid[y][x] != '1')
		return (true);
	return (false);
}

void	remove_collectable(t_map *map, int y, int x)
{
	int	mushroom_i;
	int	grid_x;
	int	grid_y;

	grid_x = x;
	grid_y = y;
	x = x * TILE_PX;
	y = y * TILE_PX;
	mushroom_i = 0;
	while (mushroom_i < map->collectables)
	{
		if (map->sprites->mushroom->instances[mushroom_i].x == x
			&& map->sprites->mushroom->instances[mushroom_i].y == y)
		{
			map->sprites->mushroom->instances[mushroom_i].enabled = false;
			map->map_grid[grid_y][grid_x] = '0';
			map->collected++;
		}
		mushroom_i++;
	}
	ft_printf("Mushrooms collected %d\n", map->collected);
}

bool	is_collectable(t_map *map, int y, int x)
{
	if (map->map_grid[y][x] == 'C')
		return (true);
	return (false);
}

void	check_game_status(t_map *map)
{
	if (map->collected == map->collectables)
	{
		map->sprites->door_closed->instances->enabled = false;
	}
	if (map->sprites->door_closed->instances->enabled == false && \
			map->start_y == map->exit_y && map->start_x == map->exit_x)
	{
		ft_printf("You've passed the map with %d moves, congratulations!!!\n", \
			map->moves);
		exit(0);
	}
}

void	move_up(t_map *map)
{
	int current_y;

	current_y = map->start_y;
	current_y--;
	if (is_collectable(map, current_y, map->start_x) == true)
		remove_collectable(map, current_y, map->start_x);
	if (collision_check(map, current_y, map->start_x) == true)
	{
		map->sprites->knight_idle->instances[0].y -= TILE_PX;
		map->start_y--;
		map->moves++;
		ft_printf("Current number of moves: %d\n", map->moves);
	}
	check_game_status(map);
	return ;
}

void	move_down(t_map *map)
{
	int current_y;

	current_y = map->start_y;
	current_y++;
	if (is_collectable(map, current_y, map->start_x) == true)
		remove_collectable(map, current_y, map->start_x);
	if (collision_check(map, current_y, map->start_x) == true)
	{
		map->sprites->knight_idle->instances[0].y += TILE_PX;
		map->start_y++;
		map->moves++;
		ft_printf("Current number of moves: %d\n", map->moves);
	}
	check_game_status(map);
	return ;
}

void	move_left(t_map *map)
{
	int current_x;

	current_x = map->start_x;
	current_x--;
	if (is_collectable(map, map->start_y, current_x) == true)
		remove_collectable(map, map->start_y, current_x);
	if (collision_check(map, map->start_y, current_x) == true)
	{
		map->sprites->knight_idle->instances[0].x -= TILE_PX;
		map->start_x--;
		map->moves++;
		ft_printf("Current number of moves: %d\n", map->moves);
	}
	check_game_status(map);
	return ;
}

void	move_right(t_map *map)
{
	int current_x;

	current_x = map->start_x;
	current_x++;
	if (is_collectable(map, map->start_y, current_x) == true)
		remove_collectable(map, map->start_y, current_x);
	if (collision_check(map, map->start_y, current_x) == true)
	{
		map->sprites->knight_idle->instances[0].x += TILE_PX;
		map->start_x++;
		map->moves++;
		ft_printf("Current number of moves: %d\n", map->moves);
	}
	check_game_status(map);
	return ;
}


void	player_mover(char flag, t_map *map)
{
	if (flag == 'W')
		move_up(map);
	if (flag == 'S')
		move_down(map);
	if (flag == 'A')
		move_left(map);
	if (flag == 'D')
		move_right(map);
}

void	my_keyhook(mlx_key_data_t keydata, void *data)
{
	t_map		*map;

	map = (t_map *) data;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(map->mlx);
		mlx_close_window(map->mlx);
		exit (0);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || \
		keydata.action == MLX_RELEASE))
		player_mover('W', map);
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || \
		keydata.action == MLX_RELEASE))
		player_mover('S', map);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || \
		keydata.action == MLX_RELEASE))
		player_mover('A', map);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || \
		keydata.action == MLX_RELEASE))
		player_mover('D', map);
}

void	set_struct(t_map *map)
{
	map->valids[0] = '0';
	map->valids[1] = '1';
	map->valids[2] = 'C';
	map->valids[3] = 'E';
	map->valids[4] = 'P';
	map->valids[5] = '\0';
}

void	exit_func(void *param)
{
	exit (0);
}
/*
void	render_main(t_map *map)
{
	mlx_image_t		*img;
	t_sprites		*sprites;

	sprites = set_sprites_struct(map->mlx, map);
	img = mlx_new_image(map->mlx, map->map_width * 32, map->map_height * 32);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(map->mlx, img, 0, 0);
	fill_background(map);
	map_rendering(map);
}*/

int	main(int ac, char **argv)
{
	t_map			map;
	mlx_image_t*	img;
	t_sprites		*sprites;

	if (ac == 2 && argv[1])
	{
		map = (t_map){};
		set_struct(&map);
		validate_file(argv[1], &map);
		map.mlx = mlx_init(map.map_width * 32, map.map_height * 32, \
		"so_long", true);
		if (!map.mlx)
			return (EXIT_FAILURE);
		render_main(&map);
		mlx_key_hook(map.mlx, &my_keyhook, &map);
		mlx_close_hook(map.mlx, &exit_func, &map);
		mlx_loop(map.mlx);
		mlx_terminate(map.mlx);
		free(map.sprites);
		free_grid(map.map_grid, map.map_height);
		exit (0);
	}
	error("INVALID INPUTS! CHECK THE PROGRAM AND MAP NAMES!", 0);
	return (1);
}
