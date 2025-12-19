/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_file.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/19 19:15:39 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

extern "C" {
	#include "parse.h"
	const char	**read_map(const char *filename);
	void		free_map(void **map);
}

static void	print_map(char **map)
{
	if (!map)
	{
		std::cout << "Map is NULL" << std::endl;
		return;
	}
	for (size_t i = 0; map[i]; i++)
	{
		std::cout << "[" << i << "] " << map[i] << std::endl;
	}
}

extern "C" void	test_map_file(const char *filename, int expected_result)
{
	const char	**input_data;
	t_map_data	map_data = {nullptr};
	int			result;

	std::cout << "\n=== Testing " << filename << " ===" << std::endl;
	input_data = read_map(filename);
	if (!input_data)
	{
		std::cout << "Failed to read file: " << filename << std::endl;
		return;
	}
	result = load_map((char **)input_data, 0, &map_data);
	if (result == expected_result)
	{
		if (result == 0)
		{
			std::cout << "✓ Test passed (valid map)" << std::endl;
			std::cout << "Map content:" << std::endl;
			print_map(map_data.map);
		}
		else
		{
			std::cout << "✓ Test passed (invalid map detected)" << std::endl;
		}
	}
	else
	{
		std::cout << "✗ Test failed (expected " << expected_result 
			<< ", got " << result << ")" << std::endl;
	}
	if (map_data.map)
	{
		for (size_t i = 0; map_data.map[i]; i++)
			free(map_data.map[i]);
		free(map_data.map);
	}
	free_map((void **)input_data);
}
