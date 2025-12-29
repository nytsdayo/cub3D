/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/28 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include "error.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#define MIN_MAP_SIZE 3
#define MAX_MAP_SIZE 1000

/**
 * @brief マップのサイズを検証する (最小/最大)
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @param max_len 最大行長
 * @return 成功: 0 / 失敗: -1
 */
int	validate_map_size(char **input_data, size_t line_index,
		size_t map_lines, size_t max_len)
{
	(void)input_data;
	(void)line_index;
	if (map_lines < MIN_MAP_SIZE)
	{
		error_msg("Error: Map size out of valid range (rows)\n");
		set_error_status(ERR_MINIMUM_MAP_SIZE);
		return (-1);
	}
	if (map_lines > MAX_MAP_SIZE || max_len > MAX_MAP_SIZE)
	{
		error_msg("Error: Map size out of valid range (columns)\n");
		set_error_status(ERR_MAXIMUM_MAP_SIZE);
		return (-1);
	}
	if (max_len < MIN_MAP_SIZE)
	{
		error_msg("Error: Map size out of valid range (columns)\n");
		set_error_status(ERR_MINIMUM_MAP_SIZE);
		return (-1);
	}
	return (0);
}

static int	count_players(char **input_data, size_t line_index,
				size_t map_lines)
{
	size_t	i;
	size_t	j;
	int		count;
	char	c;

	count = 0;
	i = 0;
	while (i < map_lines)
	{
		j = 0;
		while (input_data[line_index + i][j])
		{
			c = input_data[line_index + i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

/**
 * @brief プレイヤー開始位置が1つだけであることを検証する
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @return 成功: 0 / 失敗: -1
 */
int	validate_player_start(char **input_data, size_t line_index,
		size_t map_lines)
{
	int	player_count;

	player_count = count_players(input_data, line_index, map_lines);
	if (player_count == 0)
	{
		error_msg("Error: Map must have exactly one player start\n");
		set_error_status(ERR_PLAYER_COUNT_ZERO);
		return (-1);
	}
	if (player_count > 1)
	{
		error_msg("Error: Map must have exactly one player start\n");
		set_error_status(ERR_PLAYER_COUNT_MULTIPLE);
		return (-1);
	}
	return (0);
}

/**
 * @brief 無効な文字が含まれていないことを検証する
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @return 成功: 0 / 失敗: -1
 */
int	validate_invalid_chars(char **input_data, size_t line_index,
		size_t map_lines)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	while (i < map_lines)
	{
		j = 0;
		while (input_data[line_index + i][j])
		{
			c = input_data[line_index + i][j];
			if (!is_valid_char(c))
			{
				error_msg("Error: Invalid character in map\n");
				set_error_status(ERR_INVALID_CHARACTER);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
