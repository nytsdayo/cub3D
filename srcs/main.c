/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/11/30 18:55:35 by mkawano          ###   ########.fr       */
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
    free_map((void **)game.map);
    return (EXIT_FAILURE);
  }
  init_game(&game);
  run_game_loop(&game);
  return (EXIT_SUCCESS);
}

static int valid_args(int argc, char *argv[]) {
  if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0) {
    write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
    return (1);
  }
  return (0);
}
