/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/19 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "texture.h"
#include "utils.h"

void load_texture(t_game *game, t_img *texture, char *path) {
  texture->img = mlx_xpm_file_to_image(game->mlx, path, &game->textures.width,
                                       &game->textures.height);
  if (!texture->img) {
    write(2, "Error\nTexture loading failed: ", 30);
    write(2, path, ft_strlen(path));
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
  }
  texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
                                    &texture->line_length, &texture->endian);
}

void init_textures(t_game *game) {
  game->textures.width = TEX_WIDTH;
  game->textures.height = TEX_HEIGHT;
  load_texture(game, &game->textures.north, TEX_NORTH_PATH);
  load_texture(game, &game->textures.south, TEX_SOUTH_PATH);
  load_texture(game, &game->textures.east, TEX_EAST_PATH);
  load_texture(game, &game->textures.west, TEX_WEST_PATH);
}

void init_colors(t_game *game) {
  game->ceiling_color.r = CEILING_R;
  game->ceiling_color.g = CEILING_G;
  game->ceiling_color.b = CEILING_B;
  game->floor_color.r = FLOOR_R;
  game->floor_color.g = FLOOR_G;
  game->floor_color.b = FLOOR_B;
}
