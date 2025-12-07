/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:27:15 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/07 23:27:18 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"

static int	is_valid_position(t_game *game, double x, double y);

/*
** move_forward
** プレイヤーを前方に移動（方向ベクトルに沿って）
** 衝突判定を行い、壁がない場合のみ移動
*/
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

/*
** move_backward
** プレイヤーを後方に移動
*/
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

/*
** move_left
** プレイヤーを左に移動（カメラ平面の逆方向）
*/
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

/*
** move_right
** プレイヤーを右に移動（カメラ平面方向）
*/
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

/*
** is_valid_position
** 指定された位置が有効か（壁でないか）をチェック
*/
static int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
		return (0);
	if (game->world_map[map_y][map_x] != 0)
		return (0);
	return (1);
}
