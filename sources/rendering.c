/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:47:04 by tvalimak          #+#    #+#             */
/*   Updated: 2024/03/24 18:50:32 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
}
void    map_rendering(t_map *map)
{
    int x;
    int y;

    y = 0;
    while (y < map->map_height)
    {
        x = 0;
        while (x < map->map_width)
        {
            if (map->map_grid[y][x] == '1')
                mlx_image_to_window(map->mlx, map->sprites->wall, x * TILE_PX, y * TILE_PX);
            if (map->map_grid[y][x] == 'C')
                mlx_image_to_window(map->mlx, map->sprites->mushroom, x * TILE_PX, y * TILE_PX);
            if (map->map_grid[y][x] == 'E')
            {
                mlx_image_to_window(map->mlx, map->sprites->door_closed, x * TILE_PX, y * TILE_PX);
                mlx_image_to_window(map->mlx, map->sprites->door_open, x * TILE_PX, y * TILE_PX);
            }
            if (map->map_grid[y][x] == 'P')
                mlx_image_to_window(map->mlx, map->sprites->knight_idle, x * TILE_PX, y * TILE_PX);
            x++;
        }
        y++;
    }
}
