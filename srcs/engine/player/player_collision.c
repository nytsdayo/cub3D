/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"

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
	if (game->world_map[y1][x1] != 0)
		return (1);
	if (game->world_map[y1][x2] != 0)
		return (1);
	if (game->world_map[y2][x1] != 0)
		return (1);
	if (game->world_map[y2][x2] != 0)
		return (1);
	return (0);
}
