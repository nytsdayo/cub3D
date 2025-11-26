/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:05:14 by mkawano           #+#    #+#             */
/*   Updated: 2025/11/24 23:05:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __linux__
# include <X11/X.h>
# include <X11/keysym.h>
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TITLE "cub3D"

/* Key Codes (Cross-platform) */
#ifdef __APPLE__
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
#else
# define KEY_ESC XK_Escape
# define KEY_W XK_w
# define KEY_A XK_a
# define KEY_S XK_s
# define KEY_D XK_d
# define KEY_LEFT XK_Left
# define KEY_RIGHT XK_Right
#endif

/* Events */
#define ON_KEYDOWN 2
#define ON_DESTROY 17

typedef struct s_game {
  void *mlx;
  void *win;
  char **map;
} t_game;

#endif
