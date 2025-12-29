/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/28 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>

static int	check_side_borders(char **input_data, size_t line_index,
				size_t map_lines);

/**
 * @brief マップがすべて壁で囲まれているかを検証する（スペースを無視）
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @param max_len 最大行長
 * @return 成功: 0 / 失敗: -1
 */
int	validate_surrounded_by_walls(char **input_data, size_t line_index,
		size_t map_lines, size_t max_len)
{
	size_t	i;
	char	c;

	(void)max_len;
	i = 0;
	while (input_data[line_index][i])
	{
		c = input_data[line_index][i];
		if (c != ' ' && c != '1')
			return (set_error_status(ERR_WALL_ENCLOSURE), -1);
		i++;
	}
	i = 0;
	while (input_data[line_index + map_lines - 1][i])
	{
		c = input_data[line_index + map_lines - 1][i];
		if (c != ' ' && c != '1')
			return (set_error_status(ERR_WALL_ENCLOSURE), -1);
		i++;
	}
	return (check_side_borders(input_data, line_index, map_lines));
}

static int	check_row_borders(char **input_data, size_t line_index, size_t j)
{
	size_t	i;
	size_t	left_idx;
	size_t	right_idx;
	size_t	row_len;

	row_len = ft_strlen(input_data[line_index + j]);
	i = 0;
	while (i < row_len && input_data[line_index + j][i] == ' ')
		i++;
	left_idx = i;
	if (row_len == 0 || left_idx == row_len)
		return (0);
	i = row_len;
	while (i > left_idx && input_data[line_index + j][i - 1] == ' ')
		i--;
	if (i == 0)
		right_idx = 0;
	else
		right_idx = i - 1;
	if (input_data[line_index + j][left_idx] != '1')
		return (set_error_status(ERR_WALL_ENCLOSURE), -1);
	if (input_data[line_index + j][right_idx] != '1')
		return (set_error_status(ERR_WALL_ENCLOSURE), -1);
	return (1);
}

static int	check_side_borders(char **input_data, size_t line_index,
		size_t map_lines)
{
	size_t	j;
	int		result;

	j = 0;
	while (j < map_lines)
	{
		result = check_row_borders(input_data, line_index, j);
		if (result < 0)
			return (-1);
		j++;
	}
	return (0);
}
