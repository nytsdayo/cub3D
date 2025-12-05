/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:54:23 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 18:54:26 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h" /* for free_map */
#include <stdlib.h>

int close_window(t_game *game) {
#ifdef __linux__
  mlx_loop_end(game->mlx);
#else
  cleanup_game(game);
  exit(0);
#endif
  return (0);
}

void cleanup_game(t_game *game) {
  if (game->win)
    mlx_destroy_window(game->mlx, game->win);
  if (game->mlx) {
#ifdef __linux__
    mlx_destroy_display(game->mlx);
#endif
    free(game->mlx);
  }
  if (game->map)
    free_map((void **)game->map);
}

int handle_keypress(int keycode, t_game *game) {
  if (keycode == KEY_ESC)
    close_window(game);
  return (0);
}
