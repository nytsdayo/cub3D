/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_renderer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_RENDERER_H
# define DOOR_RENDERER_H

# include "cub3d.h"
# include "raycasting.h"

/*
** ドアのアニメーション描画
** スプライトフレームを使用してドアの開閉を表現
*/
void	draw_animated_door(t_game *game, t_ray *ray, int x);

#endif
