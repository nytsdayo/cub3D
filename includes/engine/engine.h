/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:05:14 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/24 23:15:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
#define ENGINE_H

#include "cub3d.h"

/* Init */
void init_mlx(t_game *game);
void init_game(t_game *game);

/* Game Loop */
void run_game_loop(t_game *game);

/* Renderer */
int render_frame(t_game *game);

#endif
