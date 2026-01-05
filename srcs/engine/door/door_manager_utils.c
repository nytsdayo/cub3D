/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_manager_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	init_door_row(t_game *game, int row)
{
	int	j;

	j = 0;
	while (j < game->map_width)
	{
		game->door_state[row][j] = false;
		j++;
	}
}

void	cleanup_partial_door_state(t_game *game, int last_row)
{
	while (--last_row >= 0)
		free(game->door_state[last_row]);
	free(game->door_state);
	game->door_state = NULL;
}

int	is_player_in_door(t_game *game, int door_x, int door_y)
{
	int	player_map_x;
	int	player_map_y;

	player_map_x = (int)game->player.pos_x;
	player_map_y = (int)game->player.pos_y;
	if (player_map_x == door_x && player_map_y == door_y)
		return (1);
	return (0);
}
