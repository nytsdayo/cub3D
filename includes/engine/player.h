/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:26:58 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/07 23:27:01 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

/* Vector structure for movement direction */
typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

/* Slide calculation structure */
typedef struct s_slide
{
	double	new_x;
	double	new_y;
	double	dx;
	double	dy;
	double	total;
}	t_slide;

/* Movement */
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

/* Wall sliding */
void	try_wall_slide(t_game *game, double new_x, double new_y, t_vec move);

/* Collision detection */
int		is_wall(t_game *game, double x, double y);

/* Rotation */
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

#endif