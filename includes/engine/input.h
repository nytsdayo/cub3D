/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 03:06:10 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/15 03:06:12 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "cub3d.h"

/* Window Control */
int	close_window(t_game *game);

/* Input Handling */
int	handle_keypress(int keycode, t_game *game);

#endif
