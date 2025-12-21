/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/19 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "texture.h"

void cleanup_textures(t_game *game) {
  if (game->textures.north.img)
    mlx_destroy_image(game->mlx, game->textures.north.img);
  if (game->textures.south.img)
    mlx_destroy_image(game->mlx, game->textures.south.img);
  if (game->textures.east.img)
    mlx_destroy_image(game->mlx, game->textures.east.img);
  if (game->textures.west.img)
    mlx_destroy_image(game->mlx, game->textures.west.img);
}
