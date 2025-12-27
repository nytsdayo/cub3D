/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:30:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 19:53:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycasting.h"
#include "texture.h"

/*
** レイキャスティングメイン関数
*/
void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(game, &ray, x);
		calc_step_and_side_dist(game, &ray);
		perform_dda(game, &ray);
		calc_wall_distance(game, &ray);
		calc_line_height(&ray);
		calc_texture_coords(game, &ray);
		draw_vertical_line(game, &ray, x);
		x++;
	}
}
