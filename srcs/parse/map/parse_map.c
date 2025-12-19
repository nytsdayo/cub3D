/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/19 19:18:37 by rnakatan         ###   ########.fr       */
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

/**
 * @brief 文字が有効なマップ文字かを判定する
 * @param c 判定する文字
 * @return true: 有効 / false: 無効
 */
static bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' ||
			c == 'E' || c == 'W' || c == ' ');
}

/**
 * @brief マップのサイズを検証する (最小/最大)
 * @param map マップデータ
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_map_size(char **map)
{
	size_t	rows;
	size_t	cols;

	rows = 0;
	while (map[rows])
		rows++;
	if (rows < MIN_MAP_SIZE || rows > MAX_MAP_SIZE)
	{
		fprintf(stderr, "Error: Map size must be between %d and %d rows\n",
			MIN_MAP_SIZE, MAX_MAP_SIZE);
		return (-1);
	}
	cols = ft_strlen(map[0]);
	if (cols < MIN_MAP_SIZE || cols > MAX_MAP_SIZE)
	{
		fprintf(stderr, "Error: Map size must be between %d and %d columns\n",
			MIN_MAP_SIZE, MAX_MAP_SIZE);
		return (-1);
	}
	return (0);
}

/**
 * @brief 全ての行が同じ長さであることを検証する
 * @param map マップデータ
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_row_consistency(char **map)
{
	size_t	i;
	size_t	expected_len;
	size_t	current_len;

	if (!map || !map[0])
		return (-1);
	expected_len = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		current_len = ft_strlen(map[i]);
		if (current_len != expected_len)
		{
			fprintf(stderr, "Error: Inconsistent row length at line %zu\n", i);
			return (-1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief マップがすべて壁で囲まれているかを検証する
 * @param map マップデータ
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_surrounded_by_walls(char **map)
{
	size_t	i;
	size_t	j;
	size_t	rows;
	size_t	cols;

	rows = 0;
	while (map[rows])
		rows++;
	cols = ft_strlen(map[0]);
	i = 0;
	while (i < cols)
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
			return (fprintf(stderr, "Error: Top wall missing\n"), -1);
		if (map[rows - 1][i] != '1' && map[rows - 1][i] != ' ')
			return (fprintf(stderr, "Error: Bottom wall missing\n"), -1);
		i++;
	}
	j = 0;
	while (j < rows)
	{
		if (map[j][0] != '1' && map[j][0] != ' ')
			return (fprintf(stderr, "Error: Left wall missing\n"), -1);
		if (map[j][cols - 1] != '1' && map[j][cols - 1] != ' ')
			return (fprintf(stderr, "Error: Right wall missing\n"), -1);
		j++;
	}
	return (0);
}

/**
 * @brief プレイヤー開始位置が1つだけであることを検証する
 * @param map マップデータ
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_player_start(char **map)
{
	size_t	i;
	size_t	j;
	int		player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
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
 * @param map マップデータ
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_invalid_chars(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]))
			{
				fprintf(stderr, "Error: Invalid character '%c' at line %zu, col %zu\n",
					map[i][j], i, j);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief 隣接するセルをチェックする（空きスペースが隣接していないか）
 * @param map マップデータ
 * @param i 行インデックス
 * @param j 列インデックス
 * @return true: 有効 / false: 無効
 */
static bool	check_adjacent_cells(char **map, size_t i, size_t j, size_t rows, size_t cols)
{
	if (i > 0 && map[i - 1][j] == ' ')
		return (false);
	if (i < rows - 1 && map[i + 1][j] == ' ')
		return (false);
	if (j > 0 && map[i][j - 1] == ' ')
		return (false);
	if (j < cols - 1 && map[i][j + 1] == ' ')
		return (false);
	return (true);
}

/**
 * @brief スペースが無効な位置にないことを検証する
 * @param map マップデータ
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_spaces(char **map)
{
	size_t	i;
	size_t	j;
	size_t	rows;
	size_t	cols;

	rows = 0;
	while (map[rows])
		rows++;
	cols = ft_strlen(map[0]);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if ((map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W'))
			{
				if (!check_adjacent_cells(map, i, j, rows, cols))
				{
					fprintf(stderr, "Error: Open space adjacent to void at (%zu, %zu)\n", i, j);
					return (-1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief マップセクション全体の検証を行う（内部用ヘルパー）
 * @param map マップデータ
 * @return 成功: 0 / 失敗: -1
 */
static int	validate_map_data(char **map)
{
	if (!map || !map[0])
		return (-1);
	if (validate_invalid_chars(map) != 0)
		return (-1);
	if (validate_map_size(map) != 0)
		return (-1);
	if (validate_player_start(map) != 0)
		return (-1);
	if (validate_row_consistency(map) != 0)
		return (-1);
	if (validate_surrounded_by_walls(map) != 0)
		return (-1);
	if (validate_spaces(map) != 0)
		return (-1);
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

/**
 * @brief マップセクションの構文を検証する（値の確保は行わない）
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @return 成功: 0 / 失敗: -1
 */
int	validate_map(char **input_data, size_t line_index)
{
	size_t	map_lines;
	size_t	max_len;
	size_t	i;
	size_t	j;
	char	**normalized_map;
	int		result;

	map_lines = count_map_lines(input_data, line_index);
	if (map_lines < MIN_MAP_SIZE)
	{
		fprintf(stderr, "Error: Map must have at least %d lines\n", MIN_MAP_SIZE);
		return (-1);
	}
	max_len = get_max_line_length(input_data, line_index, map_lines);
	normalized_map = malloc(sizeof(char *) * (map_lines + 1));
	if (!normalized_map)
		return (-1);
	i = 0;
	while (i < map_lines)
	{
		normalized_map[i] = calloc(max_len + 1, sizeof(char));
		if (!normalized_map[i])
		{
			while (i > 0)
				free(normalized_map[--i]);
			free(normalized_map);
			return (-1);
		}
		j = 0;
		while (j < max_len)
		{
			if (j < ft_strlen(input_data[line_index + i]))
				normalized_map[i][j] = input_data[line_index + i][j];
			else
				normalized_map[i][j] = ' ';
			j++;
		}
		normalized_map[i][max_len] = '\0';
		i++;
	}
	normalized_map[map_lines] = NULL;
	result = validate_map_data(normalized_map);
	i = 0;
	while (i < map_lines)
		free(normalized_map[i++]);
	free(normalized_map);
	return (result);
}

/**
 * @brief マップデータをメモリに読み込む
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_data マップデータを格納する構造体
 * @return 成功: 0 / 失敗: -1
 */
int	load_map(char **input_data, size_t line_index, t_map_data *map_data)
{
	size_t	map_lines;
	size_t	max_len;
	size_t	i;
	size_t	j;

	if (!input_data || !map_data)
		return (-1);
	if (validate_map(input_data, line_index) != 0)
		return (-1);
	map_lines = count_map_lines(input_data, line_index);
	max_len = get_max_line_length(input_data, line_index, map_lines);
	map_data->map = malloc(sizeof(char *) * (map_lines + 1));
	if (!map_data->map)
		return (-1);
	i = 0;
	while (i < map_lines)
	{
		map_data->map[i] = calloc(max_len + 1, sizeof(char));
		if (!map_data->map[i])
		{
			while (i > 0)
				free(map_data->map[--i]);
			free(map_data->map);
			map_data->map = NULL;
			return (-1);
		}
		j = 0;
		while (j < max_len)
		{
			if (j < ft_strlen(input_data[line_index + i]))
				map_data->map[i][j] = input_data[line_index + i][j];
			else
				map_data->map[i][j] = ' ';
			j++;
		}
		map_data->map[i][max_len] = '\0';
		i++;
	}
	map_data->map[map_lines] = NULL;
	return (0);
}
