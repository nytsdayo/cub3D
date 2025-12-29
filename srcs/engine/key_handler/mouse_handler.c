/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/30 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_handler.h"
#include "player.h"

/*
** handle_mouse_move
** マウス移動イベントハンドラー
** 画面中心からのマウス位置差分で視点を回転
*/
int handle_mouse_move(int x, int y, t_game *game) {
  int center_x;
  int center_y;
  double delta_x;

  (void)y;
  center_x = WINDOW_WIDTH / 2;
  center_y = WINDOW_HEIGHT / 2;
  delta_x = (double)(x - center_x);
  if (delta_x != 0) {
    rotate_by_angle(game, delta_x * MOUSE_SENSITIVITY);
    mlx_mouse_move(game->mlx, game->win, center_x, center_y);
  }
  return (0);
}
