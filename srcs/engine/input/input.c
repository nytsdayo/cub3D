/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:06:22 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/15 03:06:25 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "input.h"
#include "player.h"
#include "utils.h"
#include <stdlib.h>

static void	platform_close(t_game *game);

int	close_window(t_game *game)
{
	platform_close(game);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		rotate_left(game);
	else if (keycode == KEY_RIGHT)
		rotate_right(game);
	return (0);
}

#ifdef __linux__

static void	platform_close(t_game *game)
{
	mlx_loop_end(game->mlx);
}

#else

static void	platform_close(t_game *game)
{
	cleanup_game(game);
	exit(0);
}

#endif
