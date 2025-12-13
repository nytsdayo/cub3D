/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 09:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 09:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static void	print_map(char **map)
{
	size_t	i;

	if (!map)
	{
		printf("Map is NULL\n");
		return;
	}
	i = 0;
	while (map[i])
	{
		printf("[%zu] %s\n", i, map[i]);
		i++;
	}
}

static void	test_map_file(const char *filename, int expected_result)
{
	const char	**input_data;
	t_map_data	map_data;
	int			result;

	printf("\n=== Testing %s ===\n", filename);
	input_data = read_map(filename);
	if (!input_data)
	{
		printf("Failed to read file: %s\n", filename);
		return;
	}
	map_data.map = NULL;
	result = load_map((char **)input_data, 0, &map_data);
	if (result == expected_result)
	{
		if (result == 0)
		{
			printf("✓ Test passed (valid map)\n");
			printf("Map content:\n");
			print_map(map_data.map);
		}
		else
		{
			printf("✓ Test passed (invalid map detected)\n");
		}
	}
	else
	{
		printf("✗ Test failed (expected %d, got %d)\n", expected_result, result);
	}
	if (map_data.map)
	{
		size_t i = 0;
		while (map_data.map[i])
			free(map_data.map[i++]);
		free(map_data.map);
	}
	free_map((void **)input_data);
}

int	main(void)
{
	printf("===== Parse Map Module Tests =====\n");
	
	/* Valid maps */
	test_map_file("assets/maps/test/valid_simple.cub", 0);
	test_map_file("assets/maps/test/valid_medium.cub", 0);
	test_map_file("assets/maps/test/valid_with_spaces.cub", 0);
	
	/* Invalid maps */
	test_map_file("assets/maps/test/invalid_no_player.cub", -1);
	test_map_file("assets/maps/test/invalid_two_players.cub", -1);
	test_map_file("assets/maps/test/invalid_no_wall.cub", -1);
	test_map_file("assets/maps/test/invalid_too_small.cub", -1);
	test_map_file("assets/maps/test/invalid_bad_char.cub", -1);
	
	printf("\n===== All Tests Completed =====\n");
	return (0);
}
