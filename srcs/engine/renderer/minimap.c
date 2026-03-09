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
#include "minimap_utils.h"

static void	draw_minimap_cell(t_game *game, t_minimap_ctx *ctx)
{
	int	i;
	int	j;

	i = 0;
	while (i < ctx->tile_size)
	{
		j = 0;
		while (j < ctx->tile_size)
		{
			draw_minimap_pixel(game, ctx, i, j);
			j++;
		}
		i++;
	}
}

static void	draw_player_on_minimap(t_game *game, int px, int py)
{
	int	i;
	int	j;

	i = -3;
	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			draw_player_pixel(game, px + j, py + i);
			j++;
		}
		i++;
	}
}

static void	render_map_cells(t_game *game, int tile_size)
{
	t_minimap_ctx	ctx;
	int				map_x;
	int				map_y;

	ctx.tile_size = tile_size;
	map_y = 0;
	while (map_y < game->map_height)
	{
		map_x = 0;
		while (map_x < game->map_width)
		{
			ctx.screen_x = map_x * tile_size;
			ctx.screen_y = map_y * tile_size;
			ctx.color = get_cell_color(game, map_x, map_y);
			draw_minimap_cell(game, &ctx);
			map_x++;
		}
		map_y++;
	}
}

void	render_minimap(t_game *game)
{
	int	tile_size;
	int	player_x;
	int	player_y;

	tile_size = calculate_tile_size(game);
	if (tile_size < 1)
		tile_size = 1;
	render_map_cells(game, tile_size);
	player_x = (int)(game->player.pos_x * tile_size);
	player_y = (int)(game->player.pos_y * tile_size);
	draw_player_on_minimap(game, player_x, player_y);
}
