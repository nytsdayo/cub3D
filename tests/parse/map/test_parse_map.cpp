/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_map.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 09:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/20 00:46:24 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_map_file.h"
#include <iostream>

int	main(void)
{
	std::cout << "===== Parse Map Module Tests =====" << std::endl;
	
	// Valid maps
	test_map_file("test_data/map/valid_simple.cub", 0);
	test_map_file("test_data/map/valid_medium.cub", 0);
	test_map_file("test_data/map/valid_with_spaces.cub", 0);
	
	// Invalid maps
	test_map_file("test_data/map/invalid_no_player.cub", -1);
	test_map_file("test_data/map/invalid_two_players.cub", -1);
	test_map_file("test_data/map/invalid_no_wall.cub", -1);
	test_map_file("test_data/map/invalid_too_small.cub", -1);
	test_map_file("test_data/map/invalid_bad_char.cub", -1);
	
	std::cout << "\n===== All Tests Completed =====" << std::endl;
	return 0;
}
