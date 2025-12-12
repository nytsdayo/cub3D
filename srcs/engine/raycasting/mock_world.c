/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:52:24 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 19:53:46 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycasting.h"

/*
** ハードコードされた8x8マップを初期化
** 1 = 壁、0 = 空間
** 外周は全て壁で囲まれている必要がある
**
** TODO: テスト用の仮実装
** 統合時にパーサーが読み込んだマップデータに置き換える
*/
static void init_map_rows(int temp_map[MAP_HEIGHT][MAP_WIDTH]) {
  int row[MAP_WIDTH];
  int i;

  i = 0;
  row[0] = 1;
  row[1] = 1;
  row[2] = 1;
  row[3] = 1;
  row[4] = 1;
  row[5] = 1;
  row[6] = 1;
  row[7] = 1;
  while (i < MAP_WIDTH) {
    temp_map[0][i] = row[i];
    temp_map[7][i] = row[i];
    i++;
  }
}

static void init_map_middle(int temp_map[MAP_HEIGHT][MAP_WIDTH]) {
  temp_map[1][0] = 1;
  temp_map[1][7] = 1;
  temp_map[2][0] = 1;
  temp_map[2][2] = 1;
  temp_map[2][5] = 1;
  temp_map[2][7] = 1;
  temp_map[3][0] = 1;
  temp_map[3][7] = 1;
  temp_map[4][0] = 1;
  temp_map[4][2] = 1;
  temp_map[4][3] = 1;
  temp_map[4][4] = 1;
  temp_map[4][5] = 1;
  temp_map[4][7] = 1;
  temp_map[5][0] = 1;
  temp_map[5][7] = 1;
  temp_map[6][0] = 1;
  temp_map[6][7] = 1;
}

void init_hardcoded_map(t_game *game) {
  int temp_map[MAP_HEIGHT][MAP_WIDTH];
  int i;
  int j;

  i = 0;
  while (i < MAP_HEIGHT) {
    j = 0;
    while (j < MAP_WIDTH) {
      temp_map[i][j] = 0;
      j++;
    }
    i++;
  }
  init_map_rows(temp_map);
  init_map_middle(temp_map);
  i = 0;
  while (i < MAP_HEIGHT) {
    j = 0;
    while (j++ < MAP_WIDTH)
      game->world_map[i][j - 1] = temp_map[i][j - 1];
    i++;
  }
}

/*
** プレイヤーの初期位置と方向を設定
** pos: プレイヤーの位置（マップ座標）
** dir: プレイヤーの向き（方向ベクトル）
** plane: カメラ平面（視野角を決定）
**
** TODO: テスト用の仮実装
** 統合時にパーサーが読み込んだプレイヤーデータに置き換える
*/
void init_player(t_game *game) {
  game->player.pos_x = 4.5;
  game->player.pos_y = 4.5;
  game->player.dir_x = -1.0;
  game->player.dir_y = 0.0;
  game->player.plane_x = 0.0;
  game->player.plane_y = 0.66;
}

/*
---------------------------------------------------
■ 1. pos_x, pos_y - プレイヤーの位置

マップ（上から見た図）:
  0   1   2   3   4   5   6   7
0 1   1   1   1   1   1   1   1
1 1   0   0   0   0   0   0   1
2 1   0   1   0   0   1   0   1
3 1   0   0   0   0   0   0   1
4 1   0   1   1  [P]  1   0   1  ← (4.5, 4.5)
5 1   0   0   0   0   0   0   1
6 1   0   0   0   0   0   0   1
7 1   1   1   1   1   1   1   1

---------------------------------------------------
■ 2. dir_x, dir_y - プレイヤーの向き

game->player.dir_x = -1.0;  // X方向: -1（左）
game->player.dir_y = 0.0;   // Y方向: 0（変化なし）

方向の例:
北（上）:  dir_x = -1.0, dir_y =  0.0
南（下）:  dir_x =  1.0, dir_y =  0.0
東（右）:  dir_x =  0.0, dir_y =  1.0
西（左）:  dir_x =  0.0, dir_y = -1.0

北東: dir_x = -0.707, dir_y =  0.707

長さは必ず1: sqrt(dir_x² + dir_y²) = 1

---------------------------------------------------
■ 3. plane_x, plane_y - カメラ平面（視野角）

カメラ平面ベクトル：視野の幅を決定

game->player.plane_x = 0.0;   // dirに垂直
game->player.plane_y = 0.66;  // 視野角を決定

- planeはdirに垂直
- planeの長さが視野角（FOV）を決定
- 長さ0.66 ≈ FOV 66度

                カメラ平面
                        |
        -------+-------
                        |
                        [P]  ← プレイヤー
                        ↓
                        dir

プレイヤーの視野:
        左端レイ ←  plane  → 右端レイ
                        \      |      /
                        \     |     /
                        \    ↓    /
                        \  dir  /
                                \  |  /
                                \ | /
                                [P]
*/
