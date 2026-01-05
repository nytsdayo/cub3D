/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door_utils.h"
#include <stdlib.h>

/*
** ドア状態配列の初期化
** すべてのドアを閉じた状態(false)で初期化
*/
void	init_door_state(t_game *game)
{
	int	i;

	game->door_state = malloc(sizeof(bool *) * game->map_height);
	if (!game->door_state)
		return ;
	i = 0;
	while (i < game->map_height)
	{
		game->door_state[i] = malloc(sizeof(bool) * game->map_width);
		if (!game->door_state[i])
		{
			cleanup_partial_door_state(game, i);
			return ;
		}
		init_door_row(game, i);
		i++;
	}
}

/*
** ドア状態配列のメモリ解放
*/
void	free_door_state(t_game *game)
{
	int	i;

	if (!game->door_state)
		return ;
	i = 0;
	while (i < game->map_height)
	{
		free(game->door_state[i]);
		i++;
	}
	free(game->door_state);
	game->door_state = NULL;
}

/*
** ドアの開閉を切り替える
** プレイヤーがドア内にいる場合は閉じられない
*/
void	toggle_door(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return ;
	if (game->world_map[map_y][map_x] != DOOR)
		return ;
	if (game->door_state[map_y][map_x] && is_player_in_door(game, map_x, map_y))
		return ;
	game->door_state[map_y][map_x] = !game->door_state[map_y][map_x];
}

/*
** プレイヤーの前方にあるドアを開閉
** 最大2マスの範囲でドアを探す
*/
void	interact_door(t_game *game)
{
	double	check_x;
	double	check_y;
	int		map_x;
	int		map_y;
	double	distance;

	distance = 0.5;
	while (distance <= 2.0)
	{
		check_x = game->player.pos_x + game->player.dir_x * distance;
		check_y = game->player.pos_y + game->player.dir_y * distance;
		map_x = (int)check_x;
		map_y = (int)check_y;
		if (map_x >= 0 && map_x < game->map_width
			&& map_y >= 0 && map_y < game->map_height)
		{
			if (game->world_map[map_y][map_x] == DOOR)
			{
				toggle_door(game, map_x, map_y);
				return ;
			}
		}
		distance += 0.5;
	}
}
