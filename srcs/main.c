/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:05:14 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/24 23:05:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"
#include "parse.h"
#include "utils.h"
#include <stdlib.h>

static int valid_args(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  t_game game;

  if (valid_args(argc, argv) != 0)
    return (EXIT_FAILURE);
  game.map = (char **)read_map(argv[1]);
  if (game.map == NULL) {
    write(2, "Error\nFailed to read map\n", 25);
    return (EXIT_FAILURE);
  }
  if (parse((const char **)game.map) != 0) {
    /* parse error message should be handled inside parse */
    return (EXIT_FAILURE);
  }
  init_game(&game);
  mlx_key_hook(game.win, handle_keypress, &game);
  mlx_hook(game.win, ON_DESTROY, 0, close_window, &game);
  mlx_loop_hook(game.mlx, render_frame, &game);
  mlx_loop(game.mlx);
  cleanup_game(&game);
  return (EXIT_SUCCESS);
}

static int valid_args(int argc, char *argv[]) {
  if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0) {
    write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
    return (1);
  }
  return (0);
}
