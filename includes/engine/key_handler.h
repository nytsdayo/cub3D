/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:06:10 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/25 19:52:02 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include "cub3d.h"

/* Window Control */
int close_window(t_game *game);

/* Input Handling */
int handle_keypress(int keycode, t_game *game);
int handle_keyrelease(int keycode, t_game *game);
void process_held_keys(t_game *game);

#endif
