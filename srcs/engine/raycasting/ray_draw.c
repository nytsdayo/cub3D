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
#include "texture.h"

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
** RGB値から色を作成
*/
static int	create_rgb_color(t_rgb color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

/*
** 垂直線を描画（天井、テクスチャ壁、床）
*/
void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	t_img	*texture;

	y = 0;
	while (y < ray->draw_start)
		put_pixel(game, x, y++, create_rgb_color(game->ceiling_color));
	texture = select_wall_texture(game, ray);
	step = (double)TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2
			+ ray->line_height / 2) * step;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		put_pixel(game, x, y++, get_texture_pixel(texture,
				ray->tex_x, tex_y));
	}
	while (y < WINDOW_HEIGHT)
		put_pixel(game, x, y++, create_rgb_color(game->floor_color));
}
