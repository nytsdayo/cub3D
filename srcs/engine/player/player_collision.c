/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"

static int	is_blocked_cell(t_game *game, int map_x, int map_y)
{
	int	cell_type;

	cell_type = game->world_map[map_y][map_x];
	if (cell_type == WALL)
		return (1);
	if (cell_type == DOOR && !game->door_state[map_y][map_x])
		return (1);
	return (0);
}

/*
** is_wall
** 指定位置の当たり判定をマージン付きでチェック
** プレイヤーのバウンディングボックス四隅を確認
*/
int	is_wall(t_game *game, double x, double y)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;

	x1 = (int)(x - COLLISION_MARGIN);
	x2 = (int)(x + COLLISION_MARGIN);
	y1 = (int)(y - COLLISION_MARGIN);
	y2 = (int)(y + COLLISION_MARGIN);
	if (x1 < 0 || x2 >= game->map_width || y1 < 0 || y2 >= game->map_height)
		return (1);
	if (is_blocked_cell(game, x1, y1))
		return (1);
	if (is_blocked_cell(game, x2, y1))
		return (1);
	if (is_blocked_cell(game, x1, y2))
		return (1);
	if (is_blocked_cell(game, x2, y2))
		return (1);
	return (0);
}
