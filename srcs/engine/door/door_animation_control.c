/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation_control.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door_animation.h"

/*
** ドアのアニメーションを開始
** opening: 1なら開く、0なら閉じる
*/
void	start_door_animation(t_game *game, int map_x, int map_y, int opening)
{
	t_door_animation	*anim;

	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return ;
	anim = &game->door_animations[map_y][map_x];
	if (opening)
	{
		if (anim->state == DOOR_CLOSED || anim->state == DOOR_CLOSING)
			anim->state = DOOR_OPENING;
	}
	else
	{
		if (anim->state == DOOR_OPEN || anim->state == DOOR_OPENING)
			anim->state = DOOR_CLOSING;
	}
}

/*
** ドアの開き具合を0.0〜1.0の範囲で取得
** 0.0 = 完全に閉じている
** 1.0 = 完全に開いている
*/
float	get_door_open_ratio(t_game *game, int map_x, int map_y)
{
	t_door_animation	*anim;

	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (0.0f);
	anim = &game->door_animations[map_y][map_x];
	return ((float)anim->frame / (float)DOOR_ANIMATION_FRAMES);
}
