/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycasting.h"
#include "minimap_utils.h"

int	calculate_tile_size(t_game *game)
{
	int	tile_w;
	int	tile_h;

	tile_w = MINIMAP_SIZE / game->map_width;
	tile_h = MINIMAP_SIZE / game->map_height;
	if (tile_w < tile_h)
		return (tile_w);
	return (tile_h);
}

int	get_cell_color(t_game *game, int map_x, int map_y)
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

void	draw_minimap_pixel(t_game *game, t_minimap_ctx *ctx, int i, int j)
{
	if (ctx->screen_x + j < MINIMAP_SIZE
		&& ctx->screen_y + i < MINIMAP_SIZE)
	{
		put_pixel(game, MINIMAP_OFFSET + ctx->screen_x + j,
			MINIMAP_OFFSET + ctx->screen_y + i, ctx->color);
	}
}

void	draw_player_pixel(t_game *game, int x, int y)
{
	if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
		put_pixel(game, MINIMAP_OFFSET + x, MINIMAP_OFFSET + y, 0xFF0000);
}
