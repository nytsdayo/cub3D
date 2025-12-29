/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_coords.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/19 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycasting.h"

void	calc_texture_coords(t_game *game, t_ray *ray)
{
	t_img	*texture;

	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		texture = &game->textures.east;
	else if (ray->side == 0 && ray->ray_dir_x >= 0)
		texture = &game->textures.west;
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		texture = &game->textures.south;
	else
		texture = &game->textures.north;
	ray->tex_x = (int)(ray->wall_x * (double)texture->width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_x = texture->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y >= 0)
		ray->tex_x = texture->width - ray->tex_x - 1;
}
