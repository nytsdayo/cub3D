/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
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
#include <stdbool.h>

/**
 * @brief 文字が有効なマップ文字かを判定する
 * @param c 判定する文字
 * @return true: 有効 / false: 無効
 */
bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

/**
 * @brief マップの行数を数える
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @return マップの行数
 */
size_t	count_map_lines(char **input_data, size_t line_index)
{
	size_t	i;
	size_t	last_content;
	int		found_content;

	i = line_index;
	last_content = line_index;
	found_content = 0;
	while (input_data[i])
	{
		if (!is_blank_line(input_data[i]))
		{
			last_content = i;
			found_content = 1;
		}
		i++;
	}
	if (!found_content)
		return (0);
	return (last_content - line_index + 1);
}

/**
 * @brief 最大行長を取得する
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @return 最大行長
 */
size_t	get_max_line_length(char **input_data, size_t line_index,
		size_t map_lines)
{
	size_t	i;
	size_t	max_len;
	size_t	current_len;

	max_len = 0;
	i = 0;
	while (i < map_lines)
	{
		current_len = ft_strlen(input_data[line_index + i]);
		if (current_len > max_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

/**
 * @brief 指定された位置の文字を取得（範囲外ならスペース）
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param row 行インデックス
 * @param col 列インデックス
 * @return 文字（範囲外ならスペース）
 */
char	get_char_at(char **input_data, size_t line_index,
		size_t row, size_t col)
{
	size_t	line_len;

	if (!input_data[line_index + row])
		return (' ');
	line_len = ft_strlen(input_data[line_index + row]);
	if (col >= line_len)
		return (' ');
	return (input_data[line_index + row][col]);
}
