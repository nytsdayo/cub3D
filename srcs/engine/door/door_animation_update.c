/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation_update.c                            :+:      :+:    :+:   */
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
** 開くアニメーションの更新
*/
static void	update_opening_animation(t_door_animation *anim)
{
	anim->frame++;
	if (anim->frame >= DOOR_ANIMATION_FRAMES)
	{
		anim->frame = DOOR_ANIMATION_FRAMES;
		anim->state = DOOR_OPEN;
	}
}

/*
** 閉じるアニメーションの更新
*/
static void	update_closing_animation(t_door_animation *anim)
{
	anim->frame--;
	if (anim->frame <= 0)
	{
		anim->frame = 0;
		anim->state = DOOR_CLOSED;
	}
}

/*
** 単一ドアのアニメーション状態を更新
*/
static void	update_single_door_animation(t_door_animation *anim)
{
	anim->frame_timer++;
	if (anim->frame_timer < DOOR_FRAME_DURATION)
		return ;
	anim->frame_timer = 0;
	if (anim->state == DOOR_OPENING)
		update_opening_animation(anim);
	else if (anim->state == DOOR_CLOSING)
		update_closing_animation(anim);
}

/*
** すべてのドアのアニメーションを更新
** 毎フレーム呼び出される
*/
void	update_door_animations(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->world_map[y][x] == DOOR)
				update_single_door_animation(&game->door_animations[y][x]);
			x++;
		}
		y++;
	}
}
