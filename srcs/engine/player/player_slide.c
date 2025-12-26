/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_slide.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/21 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"

static int is_wall(t_game *game, double x, double y);
static void try_slide(t_game *game, t_slide *s);

/*
** try_wall_slide
** 壁スライディング処理: 閾値ベースの判定と後方移動防止
*/
void try_wall_slide(t_game *game, double new_x, double new_y, t_vec move) {
  t_slide s;

  s.new_x = new_x;
  s.new_y = new_y;
  s.dx = move.x * MOVE_SPEED;
  s.dy = move.y * MOVE_SPEED;
  if (s.dx < 0)
    s.dx = -s.dx;
  if (s.dy < 0)
    s.dy = -s.dy;
  s.total = s.dx + s.dy;
  try_slide(game, &s);
}

/*
** try_slide
** 主要軸判定に基づいてスライド方向を決定
*/
static void try_slide(t_game *game, t_slide *s) {
  if (s->dy / s->total >= 0.8 && !is_wall(game, game->player.pos_x, s->new_y))
    game->player.pos_y = s->new_y;
  else if (s->dx / s->total >= 0.8 &&
           !is_wall(game, s->new_x, game->player.pos_y))
    game->player.pos_x = s->new_x;
  else if (s->dy / s->total < 0.8 && s->dx / s->total < 0.8) {
    if (!is_wall(game, s->new_x, game->player.pos_y) &&
        (s->new_x - game->player.pos_x) * game->player.dir_x >= 0)
      game->player.pos_x = s->new_x;
    else if (!is_wall(game, game->player.pos_x, s->new_y) &&
             (s->new_y - game->player.pos_y) * game->player.dir_y >= 0)
      game->player.pos_y = s->new_y;
  }
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
