/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycasting.h"

#define MINIMAP_SIZE 150
#define MINIMAP_OFFSET 10

static int	calculate_tile_size(t_game *game)
{
	int	tile_w;
	int	tile_h;

	tile_w = MINIMAP_SIZE / game->map_width;
	tile_h = MINIMAP_SIZE / game->map_height;
	if (tile_w < tile_h)
		return (tile_w);
	return (tile_h);
}

static int	get_cell_color(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (0x000000);
	if (game->world_map[map_y][map_x] == WALL)
		return (0xFFFFFF);
	if (game->world_map[map_y][map_x] == DOOR)
	{
		if (game->door_state[map_y][map_x])
			return (0x00FF00);
		return (0x8B4513);
	}
	return (0x000000);
}

static void	draw_minimap_cell(t_game *game, int screen_x, int screen_y,
		int tile_size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			if (screen_x + j < MINIMAP_SIZE && screen_y + i < MINIMAP_SIZE)
			{
				put_pixel(game, MINIMAP_OFFSET + screen_x + j,
					MINIMAP_OFFSET + screen_y + i, color);
			}
			j++;
		}
		i++;
	}
}

static void	draw_player_on_minimap(t_game *game, int player_screen_x,
		int player_screen_y)
{
	int	i;
	int	j;
	int	radius;

	radius = 3;
	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (player_screen_x + j >= 0 && player_screen_x + j < MINIMAP_SIZE
				&& player_screen_y + i >= 0
				&& player_screen_y + i < MINIMAP_SIZE)
			{
				put_pixel(game, MINIMAP_OFFSET + player_screen_x + j,
					MINIMAP_OFFSET + player_screen_y + i, 0xFF0000);
			}
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;
	int	player_screen_x;
	int	player_screen_y;
	int	tile_size;

	tile_size = calculate_tile_size(game);
	if (tile_size < 1)
		tile_size = 1;
	map_y = 0;
	while (map_y < game->map_height)
	{
		map_x = 0;
		while (map_x < game->map_width)
		{
			screen_x = map_x * tile_size;
			screen_y = map_y * tile_size;
			draw_minimap_cell(game, screen_x, screen_y, tile_size,
				get_cell_color(game, map_x, map_y));
			map_x++;
		}
		map_y++;
	}
	player_screen_x = (int)(game->player.pos_x * tile_size);
	player_screen_y = (int)(game->player.pos_y * tile_size);
	draw_player_on_minimap(game, player_screen_x, player_screen_y);
}
