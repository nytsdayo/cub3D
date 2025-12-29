/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:51:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 19:51:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycasting.h"

/*
** DDAアルゴリズムで壁を探す
*/
void perform_dda(t_game *game, t_ray *ray) {
  while (ray->hit == 0) {
    if (ray->side_dist_x < ray->side_dist_y) {
      ray->side_dist_x += ray->delta_dist_x;
      ray->map_x += ray->step_x;
      ray->side = 0;
    } else {
      ray->side_dist_y += ray->delta_dist_y;
      ray->map_y += ray->step_y;
      ray->side = 1;
    }
    if (game->world_map[ray->map_y][ray->map_x] > 0)
      ray->hit = 1;
  }
}

/*
** 壁までの垂直距離を計算（魚眼効果を防ぐ）
*/
void calc_wall_distance(t_game *game, t_ray *ray) {
  if (ray->side == 0)
    ray->perp_wall_dist =
        (ray->map_x - game->player.pos_x + (1 - ray->step_x) / 2) /
        ray->ray_dir_x;
  else
    ray->perp_wall_dist =
        (ray->map_y - game->player.pos_y + (1 - ray->step_y) / 2) /
        ray->ray_dir_y;
}

/*
** 描画する線の高さを計算
*/
void calc_line_height(t_ray *ray) {
  ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
  ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
  if (ray->draw_start < 0)
    ray->draw_start = 0;
  ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
  if (ray->draw_end >= WINDOW_HEIGHT)
    ray->draw_end = WINDOW_HEIGHT - 1;
}
