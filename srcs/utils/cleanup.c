/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:54:23 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/21 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "texture.h"
#include "utils.h"

static void cleanup_mlx(void *mlx);

void cleanup_game(t_game *game) {
  int i;

  if (game->mlx && game->textures.north.img)
    cleanup_textures(game);
  if (game->mlx && game->img.img)
    mlx_destroy_image(game->mlx, game->img.img);
  if (game->mlx && game->win)
    mlx_destroy_window(game->mlx, game->win);
  if (game->world_map) {
    i = 0;
    while (i < game->map_height)
      free(game->world_map[i++]);
    free(game->world_map);
  }
  if (game->map)
    free_map((void **)game->map);
  if (game->mlx)
    cleanup_mlx(game->mlx);
}

#ifdef __linux__

static void cleanup_mlx(void *mlx) {
  mlx_destroy_display(mlx);
  free(mlx);
}

#else

static void cleanup_mlx(void *mlx) { free(mlx); }

#endif
