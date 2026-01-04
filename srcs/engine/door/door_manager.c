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
#include <stdlib.h>

/*
** ドア状態配列の初期化
** すべてのドアを閉じた状態(false)で初期化
*/
void	init_door_state(t_game *game)
{
	int	i;
	int	j;

	game->door_state = malloc(sizeof(bool *) * game->map_height);
	if (!game->door_state)
		return ;
	i = 0;
	while (i < game->map_height)
	{
		game->door_state[i] = malloc(sizeof(bool) * game->map_width);
		if (!game->door_state[i])
		{
			while (--i >= 0)
				free(game->door_state[i]);
			free(game->door_state);
			game->door_state = NULL;
			return ;
		}
		j = 0;
		while (j < game->map_width)
		{
			game->door_state[i][j] = false;
			j++;
		}
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
*/
void	toggle_door(t_game *game, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return ;
	if (game->world_map[map_y][map_x] == DOOR)
		game->door_state[map_y][map_x] = !game->door_state[map_y][map_x];
}

/*
** プレイヤーの前方にあるドアを開閉
*/
void	interact_door(t_game *game)
{
	double	check_x;
	double	check_y;
	int		map_x;
	int		map_y;

	check_x = game->player.pos_x + game->player.dir_x * 1.5;
	check_y = game->player.pos_y + game->player.dir_y * 1.5;
	map_x = (int)check_x;
	map_y = (int)check_y;
	toggle_door(game, map_x, map_y);
}
