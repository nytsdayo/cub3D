/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/27 05:48:48 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"
#include "parse.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

static int	valid_args(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	t_game		game;
	t_game_data	game_data;

	memset(&game, 0, sizeof(t_game));
	memset(&game_data, 0, sizeof(t_game_data));
	if (valid_args(argc, argv) != 0)
		return (EXIT_FAILURE);
	if (parse(argv[1], &game_data) != 0)
	{
		error_msg("Error\nFailed to parse map\n");
		free_config_data(&game_data.config);
		return (EXIT_FAILURE);
	}
	game.map = game_data.map.map;
	if (init_game(&game, &game_data.config) != 0)
	{
		free_map((void **)game.map);
		free_config_data(&game_data.config);
		return (EXIT_FAILURE);
	}
	run_game_loop(&game);
	free_config_data(&game_data.config);
	return (EXIT_SUCCESS);
}

static int	valid_args(int argc, char *argv[])
{
	if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0)
	{
		error_msg("Error\nUsage: ./cub3D <map.cub>\n");
		return (1);
	}
	return (0);
}
