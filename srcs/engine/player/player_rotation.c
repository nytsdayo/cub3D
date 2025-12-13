/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:27:42 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/07 23:27:45 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"
#include <math.h>

/*
** rotate_left
** プレイヤーを左に回転（反時計回り）
** 方向ベクトルとカメラ平面を回転行列で変換
*/
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(ROT_SPEED);
	sin_rot = sin(ROT_SPEED);
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_rot
		- game->player.dir_y * sin_rot;
	game->player.dir_y = old_dir_x * sin_rot
		+ game->player.dir_y * cos_rot;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos_rot
		- game->player.plane_y * sin_rot;
	game->player.plane_y = old_plane_x * sin_rot
		+ game->player.plane_y * cos_rot;
}

/*
** rotate_right
** プレイヤーを右に回転（時計回り）
*/
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(-ROT_SPEED);
	sin_rot = sin(-ROT_SPEED);
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_rot
		- game->player.dir_y * sin_rot;
	game->player.dir_y = old_dir_x * sin_rot
		+ game->player.dir_y * cos_rot;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos_rot
		- game->player.plane_y * sin_rot;
	game->player.plane_y = old_plane_x * sin_rot
		+ game->player.plane_y * cos_rot;
}
