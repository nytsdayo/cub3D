/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:54:23 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/21 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "texture.h"
#include "utils.h"
#include <stdlib.h>

static void	cleanup_mlx(void *mlx);

void	cleanup_game(t_game *game)
{
	if (game->mlx)
		cleanup_textures(game);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		cleanup_mlx(game->mlx);
	if (game->map)
		free_map((void **)game->map);
}

#ifdef __linux__

static void	cleanup_mlx(void *mlx)
{
	mlx_destroy_display(mlx);
	free(mlx);
}

#else

static void	cleanup_mlx(void *mlx)
{
	free(mlx);
}

#endif
