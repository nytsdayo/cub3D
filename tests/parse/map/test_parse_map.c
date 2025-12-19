/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 09:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/19 19:09:44 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_map_file.h"
#include <stdio.h>

int	main(void)
{
	printf("===== Parse Map Module Tests =====\n");
	
	/* Valid maps */
	test_map_file("tests/parse/map/valid_simple.cub", 0);
	test_map_file("tests/parse/map/valid_medium.cub", 0);
	test_map_file("tests/parse/map/valid_with_spaces.cub", 0);
	
	/* Invalid maps */
	test_map_file("tests/parse/map/invalid_no_player.cub", -1);
	test_map_file("tests/parse/map/invalid_two_players.cub", -1);
	test_map_file("tests/parse/map/invalid_no_wall.cub", -1);
	test_map_file("tests/parse/map/invalid_too_small.cub", -1);
	test_map_file("tests/parse/map/invalid_bad_char.cub", -1);
	
	printf("\n===== All Tests Completed =====\n");
	return (0);
}
