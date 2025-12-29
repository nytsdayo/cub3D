/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_spaces.c                                 :+:      :+:    :+:   */
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

static int	check_all_adjacent(char **input_data, size_t line_index,
				size_t map_lines, size_t i, size_t j);

/**
 * @brief スペースが無効な位置にないことを検証する
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @param max_len 最大行長
 * @return 成功: 0 / 失敗: -1
 */
int	validate_spaces(char **input_data, size_t line_index,
		size_t map_lines, size_t max_len_param)
{
	size_t	i;
	size_t	j;
	size_t	max_len;
	char	c;

	max_len = max_len_param;
	i = 0;
	while (i < map_lines)
	{
		j = 0;
		while (j < max_len)
		{
			c = get_char_at(input_data, line_index, i, j);
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (check_all_adjacent(input_data, line_index,
						map_lines, i, j) != 0)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_dir(char **input_data, size_t line_index,
				size_t map_lines, size_t i, size_t j)
{
	size_t	row_len;
	char	adj;

	if (i >= map_lines)
		return (error_msg("Error: Open space adjacent to void\n"));
	row_len = ft_strlen(input_data[line_index + i]);
	if (j >= row_len)
		return (error_msg("Error: Open space adjacent to void\n"));
	adj = input_data[line_index + i][j];
	if (adj == ' ')
		return (0);
	return (0);
}

static int	check_all_adjacent(char **input_data, size_t line_index,
		size_t map_lines, size_t i, size_t j)
{
	if (i > 0 && check_dir(input_data, line_index, map_lines, i - 1, j) != 0)
		return (-1);
	if (j > 0 && check_dir(input_data, line_index, map_lines, i, j - 1) != 0)
		return (-1);
	if (check_dir(input_data, line_index, map_lines, i + 1, j) != 0)
		return (-1);
	if (check_dir(input_data, line_index, map_lines, i, j + 1) != 0)
		return (-1);
	return (0);
}
