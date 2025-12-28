/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:06:22 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/15 03:06:25 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_handler.h"
#include "cub3d.h"
#include "player.h"
#include "utils.h"
#include <stdlib.h>

#ifdef __linux__

int close_window(t_game *game) {
  mlx_loop_end(game->mlx);
  return (0);
}

#else

int close_window(t_game *game) {
  cleanup_game(game);
  exit(0);
  return (0);
}

#endif

int handle_keypress(int keycode, t_game *game) {
  if (keycode == KEY_ESC)
    close_window(game);
  else if (keycode >= 0 && keycode < KEY_STATE_SIZE)
    game->keys[keycode] = 1;
  return (0);
}

int handle_keyrelease(int keycode, t_game *game) {
  if (keycode >= 0 && keycode < KEY_STATE_SIZE)
    game->keys[keycode] = 0;
  return (0);
}

void process_held_keys(t_game *game) {
  if (game->keys[KEY_W])
    move_forward(game);
  if (game->keys[KEY_S])
    move_backward(game);
  if (game->keys[KEY_A])
    move_left(game);
  if (game->keys[KEY_D])
    move_right(game);
  if (game->keys[KEY_LEFT])
    rotate_left(game);
  if (game->keys[KEY_RIGHT])
    rotate_right(game);
}
