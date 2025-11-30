/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 17:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "cub3d.h"

/* Raycasting Data Structure */
typedef struct s_ray {
  double camera_x;
  double ray_dir_x;
  double ray_dir_y;
  int map_x;
  int map_y;
  double side_dist_x;
  double side_dist_y;
  double delta_dist_x;
  double delta_dist_y;
  double perp_wall_dist;
  int step_x;
  int step_y;
  int hit;
  int side;
  int line_height;
  int draw_start;
  int draw_end;
} t_ray;

/* Raycasting Functions */
void cast_rays(t_game *game);
void init_hardcoded_map(t_game *game);
void init_player(t_game *game);

#endif
