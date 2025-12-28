/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/19 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "texture.h"

int get_texture_pixel(t_img *texture, int x, int y) {
  char *pixel;

  if (x < 0 || x >= TEX_WIDTH || y < 0 || y >= TEX_HEIGHT)
    return (0);
  pixel = texture->addr +
          (y * texture->line_length + x * (texture->bits_per_pixel / 8));
  return (*(unsigned int *)pixel);
}

t_img *select_wall_texture(t_game *game, t_ray *ray) {
  if (ray->side == 0) {
    if (ray->step_x > 0)
      return (&game->textures.east);
    else
      return (&game->textures.west);
  } else {
    if (ray->step_y > 0)
      return (&game->textures.south);
    else
      return (&game->textures.north);
  }
}
