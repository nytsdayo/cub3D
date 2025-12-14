/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/28 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"
#include "input.h"
#include "utils.h"

/*
** setup_event_hooks
** Sets up all MLX event hooks for the game:
** - Key press handling (for ESC, WASD, arrow keys)
** - Window close event (X button)
** - Frame rendering loop hook
*/
static void	setup_event_hooks(t_game *game)
{
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, ON_DESTROY, 0, close_window, game);
	mlx_loop_hook(game->mlx, render_frame, game);
}

/*
** run_game_loop
** Main game loop function that:
** 1. Sets up all event hooks
** 2. Starts the MLX main loop (blocks until window closes)
** 3. Performs cleanup after loop ends
*/
void	run_game_loop(t_game *game)
{
	setup_event_hooks(game);
	mlx_loop(game->mlx);
	cleanup_game(game);
}