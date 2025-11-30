/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 17:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycasting.h"

/*
** ハードコードされた8x8マップを初期化
** 1 = 壁、0 = 空間
** 外周は全て壁で囲まれている必要がある
*/
void init_hardcoded_map(t_game *game)
{
  int temp_map[MAP_HEIGHT][MAP_WIDTH] = {
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 1, 0, 0, 1, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 1, 1, 1, 1, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 0, 0, 0, 1},
      {1, 1, 1, 1, 1, 1, 1, 1}};
  int i;
  int j;

  i = 0;
  while (i < MAP_HEIGHT)
  {
    j = 0;
    while (j < MAP_WIDTH)
    {
      game->world_map[i][j] = temp_map[i][j];
      j++;
    }
    i++;
  }
}

/*
** プレイヤーの初期位置と方向を設定
** pos: プレイヤーの位置（マップ座標）
** dir: プレイヤーの向き（方向ベクトル）
** plane: カメラ平面（視野角を決定）
*/
void init_player(t_game *game)
{
  game->player.pos_x = 4.5;
  game->player.pos_y = 4.5;
  game->player.dir_x = -1.0;
  game->player.dir_y = 0.0;
  game->player.plane_x = 0.0;
  game->player.plane_y = 0.66;
}
