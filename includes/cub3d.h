/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:05:14 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/27 05:40:37 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef __linux__
#  include <X11/X.h>
#  include <X11/keysym.h>
# endif

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define TITLE "cub3D"

/* Raycasting Constants */
# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define FOV 60.0
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

/* Key State Array Size (large enough for X11 KeySym values) */
# define KEY_STATE_SIZE 70000

/* Key Codes (Cross-platform) */
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  define KEY_ESC XK_Escape
#  define KEY_W XK_w
#  define KEY_A XK_a
#  define KEY_S XK_s
#  define KEY_D XK_d
#  define KEY_LEFT XK_Left
#  define KEY_RIGHT XK_Right
# endif

/* Player Structure */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

/* Image Structure */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

/* Game Structure */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			world_map[MAP_HEIGHT][MAP_WIDTH];
	t_player	player;
	t_img		img;
	int			keys[KEY_STATE_SIZE];
}	t_game;

#endif
