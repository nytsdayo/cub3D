/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:05:14 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/24 23:05:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "utils.h" /* for free_map */

int close_window(t_game *game) {
  if (game->win)
    mlx_destroy_window(game->mlx, game->win);
  if (game->map)
    free_map((void **)game->map);
  exit(EXIT_SUCCESS);
  return (0);
}

int handle_keypress(int keycode, t_game *game) {
  if (keycode == KEY_ESC)
    close_window(game);
  return (0);
}
