/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_UTILS_H
# define DOOR_UTILS_H

# include "cub3d.h"

void	init_door_row(t_game *game, int row);
void	cleanup_partial_door_state(t_game *game, int last_row);
int		is_player_in_door(t_game *game, int door_x, int door_y);

#endif
