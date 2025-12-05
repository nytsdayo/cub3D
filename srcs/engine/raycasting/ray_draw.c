/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:52:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 19:52:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycasting.h"

/*
** ピクセルを描画
*/
void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = game->img.addr + (y * game->img.line_length + x
			* (game->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
** 垂直線を描画（天井、壁、床）
*/
void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int	y;
	int	wall_color;

	y = 0;
	while (y < ray->draw_start)
		put_pixel(game, x, y++, 0x87CEEB);
	if (ray->side == 1)
		wall_color = 0x999999;
	else
		wall_color = 0x666666;
	while (y <= ray->draw_end)
		put_pixel(game, x, y++, wall_color);
	while (y < WINDOW_HEIGHT)
		put_pixel(game, x, y++, 0x228B22);
}
