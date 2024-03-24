/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_initialization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:15:49 by tvalimak          #+#    #+#             */
/*   Updated: 2024/03/24 18:50:46 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_sprites   *load_grass_tile(mlx_t *mlx, t_sprites *sprites)
{
    mlx_texture_t   *grass;

    grass = mlx_load_png("./textures/tiles/grass tile.png");
    if (!grass)
        error ("Texture could not be loaded", 0);
    sprites->grass = mlx_texture_to_image(mlx, grass);
    if (!sprites->grass)
    {
        error ("Problem with texture to image", 0);
    }
    mlx_delete_texture (grass);
    mlx_resize_image(sprites->grass, 32, 32);
    return (sprites);
}

t_sprites   *load_mushroom_tile(mlx_t *mlx, t_sprites *sprites)
{
    mlx_texture_t   *mushroom;

    mushroom = mlx_load_png("./textures/tiles/mushroom.png");
    if (!mushroom)
        error ("Texture could not be loaded", 0);
    sprites->mushroom = mlx_texture_to_image(mlx, mushroom);
    if (!sprites->mushroom)
    {
        error ("Problem with texture to image", 0);
    }
    mlx_delete_texture (mushroom);
    mlx_resize_image(sprites->mushroom, 32, 32);
    return (sprites);
}

t_sprites   *load_wall_tile(mlx_t *mlx, t_sprites *sprites)
{
    mlx_texture_t   *wall;

    wall = mlx_load_png("./textures/tiles/wall tile.png");
    if (!wall)
        error ("Texture could not be loaded", 0);
    sprites->wall = mlx_texture_to_image(mlx, wall);
    if (!sprites->wall)
    {
        error ("Problem with texture to image", 0);
    }
    mlx_delete_texture (wall);
    mlx_resize_image(sprites->wall, 32, 32);
    return (sprites);
}

t_sprites   *load_door_open_tile(mlx_t *mlx, t_sprites *sprites)
{
    mlx_texture_t   *door_open;

    door_open = mlx_load_png("./textures/tiles/door open.png");
    if (!door_open)
        error ("Texture could not be loaded", 0);
    sprites->door_open = mlx_texture_to_image(mlx, door_open);
    if (!sprites->door_open)
    {
        error ("Problem with texture to image", 0);
    }
    mlx_delete_texture (door_open);
    mlx_resize_image(sprites->door_open, 32, 32);
    return (sprites);
}

t_sprites   *load_door_closed_tile(mlx_t *mlx, t_sprites *sprites)
{
    mlx_texture_t   *door_closed;

    door_closed = mlx_load_png("./textures/tiles/door closed.png");
    if (!door_closed)
        error ("Texture could not be loaded", 0);
    sprites->door_closed = mlx_texture_to_image(mlx, door_closed);
    if (!sprites->door_closed)
    {
        error ("Problem with texture to image", 0);
    }
    mlx_delete_texture (door_closed);
    mlx_resize_image(sprites->door_closed, 32, 32);
    return (sprites);
}

t_sprites   *load_knight_idle_tile(mlx_t *mlx, t_sprites *sprites)
{
    mlx_texture_t   *knight_idle;

    knight_idle = mlx_load_png("./textures/Player/tile000.png");
    if (!knight_idle)
        error ("Texture could not be loaded", 0);
    sprites->knight_idle = mlx_texture_to_image(mlx, knight_idle);
    if (!sprites->knight_idle)
    {
        error ("Problem with texture to image", 0);
    }
    mlx_delete_texture (knight_idle);
    mlx_resize_image(sprites->knight_idle, 32, 32);
    return (sprites);
}

t_sprites   *set_sprites_struct(mlx_t *mlx, t_map *map)
{
    t_sprites   *sprites;

    sprites = (t_sprites *)ft_calloc(1, sizeof(t_sprites));
    if (!sprites)
        return (NULL);
    sprites = load_wall_tile(mlx, sprites);
    sprites = load_grass_tile(mlx, sprites);
    sprites = load_mushroom_tile(mlx, sprites);
    sprites = load_door_closed_tile(mlx, sprites);
    sprites = load_door_open_tile(mlx, sprites);
    sprites = load_knight_idle_tile(mlx, sprites);
    map->sprites = sprites;
    return (sprites);
}
