/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2026/01/05 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_UTILS_H
# define MINIMAP_UTILS_H

# include "cub3d.h"

# define MINIMAP_SIZE 150
# define MINIMAP_OFFSET 10

typedef struct s_minimap_ctx
{
	int	tile_size;
	int	screen_x;
	int	screen_y;
	int	color;
}	t_minimap_ctx;

int		calculate_tile_size(t_game *game);
int		get_cell_color(t_game *game, int map_x, int map_y);
void	draw_minimap_pixel(t_game *game, t_minimap_ctx *ctx, int i, int j);
void	draw_player_pixel(t_game *game, int x, int y);

#endif
