/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycasting.h"
#include <stdlib.h>

static int	find_player_position(char **map, int *x, int *y, char *dir);
static void	set_player_direction(t_player *player, char direction);
static void	set_player_dir_ew(t_player *player, char direction);

static void	get_map_dimensions(char **map, int *width, int *height)
{
	int	h;
	int	w;
	int	max_w;

	h = 0;
	max_w = 0;
	while (map[h])
	{
		w = 0;
		while (map[h][w])
			w++;
		if (w > max_w)
			max_w = w;
		h++;
	}
	*width = max_w;
	*height = h;
}

static int	**allocate_world_map(int width, int height)
{
	int	**world_map;
	int	i;

	world_map = malloc(sizeof(int *) * height);
	if (!world_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		world_map[i] = malloc(sizeof(int) * width);
		if (!world_map[i])
		{
			while (i > 0)
				free(world_map[--i]);
			free(world_map);
			return (NULL);
		}
		i++;
	}
	return (world_map);
}

/*
** マップをint配列に変換
** '1' = 壁、'0' or N/S/E/W = 空間
*/
void	init_world_map(t_game *game)
{
	int	i;
	int	j;

	get_map_dimensions(game->map, &game->map_width, &game->map_height);
	game->world_map = allocate_world_map(game->map_width, game->map_height);
	if (!game->world_map)
		return ;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width && game->map[i] && game->map[i][j])
		{
			if (game->map[i][j] == '1')
				game->world_map[i][j] = 1;
			else
				game->world_map[i][j] = 0;
			j++;
		}
		while (j < game->map_width)
			game->world_map[i][j++] = 0;
		i++;
	}
}

/*
** マップからプレイヤーの初期位置と方向を設定
*/
void	init_player(t_game *game)
{
	int		player_x;
	int		player_y;
	char	direction;

	if (find_player_position(game->map, &player_x, &player_y, &direction))
	{
		game->player.pos_x = (double)player_x + 0.5;
		game->player.pos_y = (double)player_y + 0.5;
		set_player_direction(&game->player, direction);
	}
	else
	{
		game->player.pos_x = 3.5;
		game->player.pos_y = 3.5;
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
}

static int	find_player_position(char **map, int *x, int *y, char *dir)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				*y = i;
				*x = j;
				*dir = map[i][j];
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (direction == 'S')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
	else
		set_player_dir_ew(player, direction);
}

static void	set_player_dir_ew(t_player *player, char direction)
{
	if (direction == 'E')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (direction == 'W')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
}
