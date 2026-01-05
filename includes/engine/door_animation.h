/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_ANIMATION_H
# define DOOR_ANIMATION_H

# include "cub3d.h"

/*
** ドアアニメーション定数
** DOOR_ANIMATION_FRAMES: アニメーションの総フレーム数（完全に開くまで）
** DOOR_FRAME_DURATION: 各フレームの持続時間（更新回数）
*/
# define DOOR_ANIMATION_FRAMES 30
# define DOOR_FRAME_DURATION 1

/*
** ドアアニメーション状態
** DOOR_CLOSED: 完全に閉じている
** DOOR_OPENING: 開いている途中
** DOOR_OPEN: 完全に開いている
** DOOR_CLOSING: 閉じている途中
*/
typedef enum e_door_anim_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_anim_state;

/*
** ドアアニメーション情報構造体
** state: 現在のアニメーション状態
** frame: 現在のアニメーションフレーム（0-DOOR_ANIMATION_FRAMES）
** frame_timer: フレーム切り替えタイマー
*/
typedef struct s_door_animation
{
	t_door_anim_state	state;
	int					frame;
	int					frame_timer;
}	t_door_animation;

/*
** ドアアニメーション管理関数
*/
void	init_door_animations(t_game *game);
void	free_door_animations(t_game *game);
void	update_door_animations(t_game *game);
void	start_door_animation(t_game *game, int map_x, int map_y, int opening);
float	get_door_open_ratio(t_game *game, int map_x, int map_y);

#endif
