/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/28 20:20:29 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"
#include "parse.h"
#include "utils.h"

static int valid_args(int argc, char *argv[]);
static void init_structs(t_game *game, t_game_data *game_data);

int main(int argc, char *argv[]) {
  t_game game;
  t_game_data game_data;

  init_structs(&game, &game_data);
  if (valid_args(argc, argv) != 0)
    return (EXIT_FAILURE);
  if (parse(argv[1], &game_data) != 0) {
    write(2, "Error\nFailed to parse map\n", 26);
    free_config_data(&game_data.config);
    return (EXIT_FAILURE);
  }
  game.map = game_data.map.map;
  if (init_game(&game, &game_data.config) != 0) {
    free_map((void **)game.map);
    free_config_data(&game_data.config);
    return (EXIT_FAILURE);
  }
  run_game_loop(&game);
  free_config_data(&game_data.config);
  return (EXIT_SUCCESS);
}

static void init_structs(t_game *game, t_game_data *game_data) {
  int i;

  i = 0;
  while (i < (int)sizeof(t_game))
    ((char *)game)[i++] = 0;
  i = 0;
  while (i < (int)sizeof(t_game_data))
    ((char *)game_data)[i++] = 0;
}

static int valid_args(int argc, char *argv[]) {
  if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0) {
    write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
    return (1);
  }
  return (0);
}
