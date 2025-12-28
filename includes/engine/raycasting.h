/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 18:57:16 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

/* Raycasting Data Structure */
typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
}			t_ray;

/* Raycasting Functions */
void		cast_rays(t_game *game);

/* Ray Initialization */
void		init_ray(t_game *game, t_ray *ray, int x);
void		calc_step_and_side_dist(t_game *game, t_ray *ray);

/* DDA Functions */
void		perform_dda(t_game *game, t_ray *ray);
void		calc_wall_distance(t_game *game, t_ray *ray);
void		calc_line_height(t_ray *ray);

/* Texture Coordinate Calculation */
void		calc_texture_coords(t_game *game, t_ray *ray);

/* Drawing Functions */
void		put_pixel(t_game *game, int x, int y, int color);
void		draw_vertical_line(t_game *game, t_ray *ray, int x);

#endif
