/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/20 01:16:05 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MIN_MAP_SIZE 3
#define MAX_MAP_SIZE 1000

static bool		is_valid_char(char c);
static size_t	count_map_lines(char **input_data, size_t line_index);
static size_t	get_max_line_length(char **input_data, size_t line_index, size_t map_lines);
static int		validate_invalid_chars(
					char **input_data, size_t line_index, size_t map_lines);
static int		validate_map_size(char **input_data,
					size_t line_index, size_t map_lines, size_t max_len);
static int		validate_player_start(char **input_data,
					size_t line_index, size_t map_lines);
static char		get_char_at(char **input_data,
					size_t line_index, size_t row, size_t col);
static int		validate_surrounded_by_walls(
					char **input_data, size_t line_index, size_t map_lines, size_t max_len);
static int		validate_spaces(
					char **input_data, size_t line_index, size_t map_lines, size_t max_len);

/**
 * @brief マップセクションの構文を検証する（メモリ確保なし）
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @return 成功: 0 / 失敗: -1
 */
int	validate_map(char **input_data, size_t line_index)
{
	size_t	map_lines;
	size_t	max_len;

	if (!input_data || !input_data[line_index])
		return (-1);
	map_lines = count_map_lines(input_data, line_index);
	if (map_lines < MIN_MAP_SIZE)
	{
		fprintf(stderr, "Error: Map must have at least %d lines\n", MIN_MAP_SIZE);
		return (-1);
	}
	max_len = get_max_line_length(input_data, line_index, map_lines);
	if (validate_invalid_chars(input_data, line_index, map_lines) != 0)
		return (-1);
	if (validate_map_size(input_data, line_index, map_lines, max_len) != 0)
		return (-1);
	if (validate_player_start(input_data, line_index, map_lines) != 0)
		return (-1);
	if (validate_surrounded_by_walls(input_data, line_index, map_lines, max_len) != 0)
		return (-1);
	if (validate_spaces(input_data, line_index, map_lines, max_len) != 0)
		return (-1);
	return (0);
}


/**
 * @brief 文字が有効なマップ文字かを判定する
 * @param c 判定する文字
 * @return true: 有効 / false: 無効
 */
static bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

/**
 * @brief マップのサイズを検証する (最小/最大)
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @param max_len 最大行長
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_map_size(char **input_data, size_t line_index, 
							size_t map_lines, size_t max_len)
{
	(void)input_data;
	(void)line_index;
	if (map_lines < MIN_MAP_SIZE || map_lines > MAX_MAP_SIZE)
	{
		fprintf(stderr, "Error: Map size must be between %d and %d rows\n",
			MIN_MAP_SIZE, MAX_MAP_SIZE);
		return (-1);
	}
	if (max_len < MIN_MAP_SIZE || max_len > MAX_MAP_SIZE)
	{
		fprintf(stderr, "Error: Map size must be between %d and %d columns\n",
			MIN_MAP_SIZE, MAX_MAP_SIZE);
		return (-1);
	}
	return (0);
}

/**
 * @brief 指定された位置の文字を取得（範囲外ならスペース）
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param row 行インデックス
 * @param col 列インデックス
 * @return 文字（範囲外ならスペース）
 */
static char	get_char_at(char **input_data, size_t line_index, size_t row, size_t col)
{
	size_t	line_len;

	if (!input_data[line_index + row])
		return (' ');
	line_len = ft_strlen(input_data[line_index + row]);
	if (col >= line_len)
		return (' ');
	return (input_data[line_index + row][col]);
}

/**
 * @brief マップがすべて壁で囲まれているかを検証する（スペースを無視）
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @param max_len 最大行長
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_surrounded_by_walls(char **input_data, size_t line_index,
										size_t map_lines, size_t max_len)
{
	size_t	i;
	size_t	j;
	char	c;

	/* top / bottom: first and last non-space chars must be '1' */
	i = 0;
	while (i < max_len)
	{
		c = get_char_at(input_data, line_index, 0, i);
		if (c != ' ' && c != '1')
			return (fprintf(stderr, "Error: Top border must be all walls at column %zu\n", i), -1);
		c = get_char_at(input_data, line_index, map_lines - 1, i);
		if (c != ' ' && c != '1')
			return (fprintf(stderr, "Error: Bottom border must be all walls at column %zu\n", i), -1);
		i++;
	}
	/* left / right: first and last non-space chars in each row must be '1' */
	j = 0;
	while (j < map_lines)
	{
		/* Check first non-space character from left */
		i = 0;
		while (i < max_len)
		{
			c = get_char_at(input_data, line_index, j, i);
			if (c != ' ')
			{
				if (c != '1')
					return (fprintf(stderr, "Error: Left border must be all walls at row %zu\n", j), -1);
				break;
			}
			i++;
		}
		/* Check first non-space character from right */
		i = max_len;
		while (i > 0)
		{
			c = get_char_at(input_data, line_index, j, i - 1);
			if (c != ' ')
			{
				if (c != '1')
					return (fprintf(stderr, "Error: Right border must be all walls at row %zu\n", j), -1);
				break;
			}
			i--;
		}
		j++;
	}
	return (0);
}

/**
 * @brief プレイヤー開始位置が1つだけであることを検証する
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_player_start(char **input_data, size_t line_index, size_t map_lines)
{
	size_t	i;
	size_t	j;
	int		player_count;
	char	c;

	player_count = 0;
	i = 0;
	while (i < map_lines)
	{
		j = 0;
		while (input_data[line_index + i][j])
		{
			c = input_data[line_index + i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		fprintf(stderr, "Error: Map must have exactly one player start position (found %d)\n",
			player_count);
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
static int	validate_invalid_chars(char **input_data, size_t line_index, size_t map_lines)
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
				fprintf(stderr, "Error: Invalid character '%c' at line %zu, col %zu\n",
					c, i, j);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief スペースが無効な位置にないことを検証する
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @param max_len 最大行長
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_spaces(char **input_data, size_t line_index,
							size_t map_lines, size_t max_len)
{
	size_t	i;
	size_t	j;
	char	c;
	char	adj;

	i = 0;
	while (i < map_lines)
	{
		j = 0;
		while (j < max_len)
		{
			c = get_char_at(input_data, line_index, i, j);
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				/* Check adjacent cells */
				if (i > 0)
				{
					adj = get_char_at(input_data, line_index, i - 1, j);
					if (adj == ' ')
						return (fprintf(stderr, "Error: Open space adjacent to void at (%zu, %zu)\n", i, j), -1);
				}
				if (i < map_lines - 1)
				{
					adj = get_char_at(input_data, line_index, i + 1, j);
					if (adj == ' ')
						return (fprintf(stderr, "Error: Open space adjacent to void at (%zu, %zu)\n", i, j), -1);
				}
				if (j > 0)
				{
					adj = get_char_at(input_data, line_index, i, j - 1);
					if (adj == ' ')
						return (fprintf(stderr, "Error: Open space adjacent to void at (%zu, %zu)\n", i, j), -1);
				}
				if (j < max_len - 1)
				{
					adj = get_char_at(input_data, line_index, i, j + 1);
					if (adj == ' ')
						return (fprintf(stderr, "Error: Open space adjacent to void at (%zu, %zu)\n", i, j), -1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}



/**
 * @brief マップの行数を数える
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @return マップの行数
 */
static size_t	count_map_lines(char **input_data, size_t line_index)
{
	size_t	count;

	count = 0;
	while (input_data[line_index + count])
		count++;
	return (count);
}

/**
 * @brief 最大行長を取得する
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @return 最大行長
 */
static size_t	get_max_line_length(char **input_data, size_t line_index, size_t map_lines)
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
