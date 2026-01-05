/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door_renderer.h"
#include "door_animation.h"
#include "raycasting.h"

/*
** RGB値から色を作成
*/
static int	create_rgb_color(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

/*
** RGB値をクランプ（0-255の範囲に制限）
*/
static int	clamp_rgb(int value)
{
	if (value > 255)
		return (255);
	return (value);
}

/*
** アニメーションフレームに基づいてドアの色を計算
** 開くにつれて明るくなり、透明感を表現
*/
static int	get_door_color_for_frame(float open_ratio)
{
	int	base_color;
	int	r;
	int	g;
	int	b;
	int	brightness;

	base_color = 0x8B4513;
	r = (base_color >> 16) & 0xFF;
	g = (base_color >> 8) & 0xFF;
	b = base_color & 0xFF;
	brightness = (int)(open_ratio * 100);
	r = clamp_rgb(r + brightness);
	g = clamp_rgb(g + brightness);
	b = clamp_rgb(b + brightness);
	return ((r << 16) | (g << 8) | b);
}

/*
** ドアのスプライト描画（縦線を複数フレームで描画）
** open_ratio: 0.0（閉）〜 1.0（開）
*/
static void	draw_door_sprite(t_game *game, t_ray *ray, int x, float open_ratio)
{
	int		y;
	int		door_color;
	int		draw_height;
	int		vertical_offset;

	door_color = get_door_color_for_frame(open_ratio);
	draw_height = (int)(ray->line_height * (1.0f - open_ratio * 0.7f));
	vertical_offset = (ray->line_height - draw_height) / 2;
	y = 0;
	while (y < ray->draw_start + vertical_offset)
		put_pixel(game, x, y++, create_rgb_color(game->ceiling_color));
	while (y < ray->draw_start + vertical_offset + draw_height
		&& y <= ray->draw_end)
		put_pixel(game, x, y++, door_color);
	while (y <= ray->draw_end)
		put_pixel(game, x, y++, create_rgb_color(game->ceiling_color));
	while (y < WINDOW_HEIGHT)
		put_pixel(game, x, y++, create_rgb_color(game->floor_color));
}

/*
** アニメーション付きドア描画のメイン関数
*/
void	draw_animated_door(t_game *game, t_ray *ray, int x)
{
	float	open_ratio;

	open_ratio = get_door_open_ratio(game, ray->map_x, ray->map_y);
	draw_door_sprite(game, ray, x, open_ratio);
}
