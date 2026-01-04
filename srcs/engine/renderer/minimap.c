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
#define MINIMAP_TILE_SIZE 10

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
		int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_TILE_SIZE)
	{
		j = 0;
		while (j < MINIMAP_TILE_SIZE)
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

	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
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

	map_y = 0;
	while (map_y < game->map_height
		&& map_y * MINIMAP_TILE_SIZE < MINIMAP_SIZE)
	{
		map_x = 0;
		while (map_x < game->map_width
			&& map_x * MINIMAP_TILE_SIZE < MINIMAP_SIZE)
		{
			screen_x = map_x * MINIMAP_TILE_SIZE;
			screen_y = map_y * MINIMAP_TILE_SIZE;
			draw_minimap_cell(game, screen_x, screen_y,
				get_cell_color(game, map_x, map_y));
			map_x++;
		}
		map_y++;
	}
	player_screen_x = (int)(game->player.pos_x * MINIMAP_TILE_SIZE);
	player_screen_y = (int)(game->player.pos_y * MINIMAP_TILE_SIZE);
	draw_player_on_minimap(game, player_screen_x, player_screen_y);
}
