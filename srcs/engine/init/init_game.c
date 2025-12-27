/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:05:14 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 19:56:47 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"
#include "raycasting.h"
#include "texture.h"

static int init_mlx(t_game *game);
static void init_image(t_game *game);

/*
** ゲームの初期化
** MLX、画像バッファ、マップ、プレイヤーを初期化する
**
** TODO: init_hardcoded_map()とinit_player()はテスト用の仮実装。
** 統合時にパーサーが設定したデータを使用するため、これらの呼び出しは削除する。
*/
int init_game(t_game *game) {
  int i;

  game->mlx = NULL;
  game->win = NULL;
  i = 0;
  while (i < 256)
    game->keys[i++] = 0;
  if (init_mlx(game) != 0)
    return (1);
  init_image(game);
  init_textures(game);
  init_colors(game);
  init_hardcoded_map(game);
  init_player(game);
  return (0);
}

static int init_mlx(t_game *game) {
  game->mlx = mlx_init();
  if (!game->mlx) {
    write(2, "Error\nMLX init failed\n", 22);
    return (1);
  }
  game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
  if (!game->win) {
    write(2, "Error\nWindow creation failed\n", 29);
    return (1);
  }
  return (0);
}

static void init_image(t_game *game) {
  game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  if (!game->img.img) {
    write(2, "Error\nImage creation failed\n", 28);
    exit(EXIT_FAILURE);
  }
  game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
                                     &game->img.line_length, &game->img.endian);
}
