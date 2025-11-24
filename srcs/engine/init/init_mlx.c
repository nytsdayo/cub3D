/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:05:14 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/24 23:05:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"

void init_game(t_game *game) {
  game->mlx = NULL;
  game->win = NULL;
  game->map = NULL;
  init_mlx(game);
}

void init_mlx(t_game *game) {
  game->mlx = mlx_init();
  if (!game->mlx) {
    write(2, "Error\nMLX init failed\n", 22);
    exit(EXIT_FAILURE);
  }
  game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
  if (!game->win) {
    write(2, "Error\nWindow creation failed\n", 29);
    exit(EXIT_FAILURE);
  }
}
