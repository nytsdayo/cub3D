/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_slide.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/21 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player.h"

static void	try_slide(t_game *game, t_slide *s);

/*
** try_wall_slide
** 壁スライディング処理: 閾値ベースの判定と後方移動防止
*/
void	try_wall_slide(t_game *game, double new_x, double new_y, t_vec move)
{
	t_slide	s;

	s.new_x = new_x;
	s.new_y = new_y;
	s.dx = move.x * MOVE_PER_FRAME;
	s.dy = move.y * MOVE_PER_FRAME;
	if (s.dx < 0)
		s.dx = -s.dx;
	if (s.dy < 0)
		s.dy = -s.dy;
	s.total = s.dx + s.dy;
	try_slide(game, &s);
}

/*
** try_slide
** 主要軸判定に基づいてスライド方向を決定
*/
static void	try_slide(t_game *game, t_slide *s)
{
	if (s->dy / s->total >= 0.8 && !is_wall(game, game->player.pos_x, s->new_y))
		game->player.pos_y = s->new_y;
	else if (s->dx / s->total >= 0.8
		&& !is_wall(game, s->new_x, game->player.pos_y))
		game->player.pos_x = s->new_x;
	else if (s->dy / s->total < 0.8 && s->dx / s->total < 0.8)
	{
		if (!is_wall(game, s->new_x, game->player.pos_y)
			&& (s->new_x - game->player.pos_x) * game->player.dir_x >= 0)
			game->player.pos_x = s->new_x;
		else if (!is_wall(game, game->player.pos_x, s->new_y)
			&& (s->new_y - game->player.pos_y) * game->player.dir_y >= 0)
			game->player.pos_y = s->new_y;
	}
}
