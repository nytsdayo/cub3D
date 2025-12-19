/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/19 19:09:44 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Forward declarations for utility functions */
const char	**read_map(const char *filename);
void		free_map(void **map);

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

void	test_map_file(const char *filename, int expected_result)
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
