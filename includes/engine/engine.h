/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:57:35 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/30 18:57:37 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
#define ENGINE_H

#include "cub3d.h"

/* Init */
void init_game(t_game *game);

/* Game Loop */
void run_game_loop(t_game *game);

/* Renderer */
int render_frame(t_game *game);

#endif
