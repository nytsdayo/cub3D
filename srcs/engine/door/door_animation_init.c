/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door_animation.h"
#include <stdlib.h>

/*
** 単一行のドアアニメーションを初期化
*/
static void	init_animation_row(t_door_animation *row, int width)
{
	int	x;

	x = 0;
	while (x < width)
	{
		row[x].state = DOOR_CLOSED;
		row[x].frame = 0;
		row[x].frame_timer = 0;
		x++;
	}
}

/*
** メモリ割り当て失敗時のクリーンアップ
*/
static void	cleanup_animations(t_door_animation **animations, int last_row)
{
	while (--last_row >= 0)
		free(animations[last_row]);
	free(animations);
}

/*
** ドアアニメーション配列の初期化
** すべてのドアを閉じた状態で初期化
*/
void	init_door_animations(t_game *game)
{
	int	y;

	game->door_animations = malloc(sizeof(t_door_animation *)
			* game->map_height);
	if (!game->door_animations)
		return ;
	y = 0;
	while (y < game->map_height)
	{
		game->door_animations[y] = malloc(sizeof(t_door_animation)
				* game->map_width);
		if (!game->door_animations[y])
		{
			cleanup_animations(game->door_animations, y);
			game->door_animations = NULL;
			return ;
		}
		init_animation_row(game->door_animations[y], game->map_width);
		y++;
	}
}

/*
** ドアアニメーション配列のメモリ解放
*/
void	free_door_animations(t_game *game)
{
	int	i;

	if (!game->door_animations)
		return ;
	i = 0;
	while (i < game->map_height)
	{
		free(game->door_animations[i]);
		i++;
	}
	free(game->door_animations);
	game->door_animations = NULL;
}
