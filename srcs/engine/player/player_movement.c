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

static int is_wall(t_game *game, double x, double y);

/*
** move_forward
** プレイヤーを前方に移動（方向ベクトルに沿って）
** X/Y軸を個別にチェックし、壁に沿ってスライド可能にする
*/
void move_forward(t_game *game) {
  double new_x;
  double new_y;

  new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
  new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
  if (!is_wall(game, new_x, game->player.pos_y))
    game->player.pos_x = new_x;
  if (!is_wall(game, game->player.pos_x, new_y))
    game->player.pos_y = new_y;
}

/*
** move_backward
** プレイヤーを後方に移動
*/
void move_backward(t_game *game) {
  double new_x;
  double new_y;

  new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
  new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
  if (!is_wall(game, new_x, game->player.pos_y))
    game->player.pos_x = new_x;
  if (!is_wall(game, game->player.pos_x, new_y))
    game->player.pos_y = new_y;
}

/*
** move_left
** プレイヤーを左に移動（カメラ平面の逆方向）
*/
void move_left(t_game *game) {
  double new_x;
  double new_y;

  new_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED;
  new_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED;
  if (!is_wall(game, new_x, game->player.pos_y))
    game->player.pos_x = new_x;
  if (!is_wall(game, game->player.pos_x, new_y))
    game->player.pos_y = new_y;
}

/*
** move_right
** プレイヤーを右に移動（カメラ平面方向）
*/
void move_right(t_game *game) {
  double new_x;
  double new_y;

  new_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED;
  new_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED;
  if (!is_wall(game, new_x, game->player.pos_y))
    game->player.pos_x = new_x;
  if (!is_wall(game, game->player.pos_x, new_y))
    game->player.pos_y = new_y;
}

/*
** is_wall
** 指定位置の当たり判定をマージン付きでチェック
** プレイヤーのバウンディングボックス四隅を確認
*/
static int is_wall(t_game *game, double x, double y) {
  int x1;
  int x2;
  int y1;
  int y2;

  x1 = (int)(x - COLLISION_MARGIN);
  x2 = (int)(x + COLLISION_MARGIN);
  y1 = (int)(y - COLLISION_MARGIN);
  y2 = (int)(y + COLLISION_MARGIN);
  if (x1 < 0 || x2 >= MAP_WIDTH || y1 < 0 || y2 >= MAP_HEIGHT)
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
