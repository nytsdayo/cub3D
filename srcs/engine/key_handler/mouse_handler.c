/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/30 08:55:37 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "key_handler.h"
#include "player.h"

/*
** handle_mouse_press
** マウスボタン押下イベントハンドラー
*/
int	handle_mouse_press(int button, int x, int y, t_game *game)
{
	if (button == MOUSE_LEFT)
	{
		game->mouse_pressed = 1;
		game->last_mouse_x = x;
		game->last_mouse_y = y;
	}
	return (0);
}

/*
** handle_mouse_release
** マウスボタン解放イベントハンドラー
*/
int	handle_mouse_release(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		game->mouse_pressed = 0;
	return (0);
}

/*
** handle_mouse_move
** マウス移動イベントハンドラー
** 左クリック長押し中のみ視点を回転
*/
int	handle_mouse_move(int x, int y, t_game *game)
{
	double	delta_x;

	(void)y;
	if (!game->mouse_pressed)
		return (0);
	delta_x = (double)(x - game->last_mouse_x);
	if (delta_x != 0)
		rotate_by_angle(game, delta_x * MOUSE_SENSITIVITY);
	game->last_mouse_x = x;
	game->last_mouse_y = y;
	return (0);
}
