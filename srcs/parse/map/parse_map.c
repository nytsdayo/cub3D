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
#include <stdio.h>
#include <stdlib.h>

#define MIN_MAP_SIZE 3

static int run_validations(char **input_data, size_t line_index,
                           size_t map_lines, size_t max_len) {
  if (validate_invalid_chars(input_data, line_index, map_lines) != 0)
    return (-1);
  if (validate_map_size(input_data, line_index, map_lines, max_len) != 0)
    return (-1);
  if (validate_player_start(input_data, line_index, map_lines) != 0)
    return (-1);
  if (validate_surrounded_by_walls(input_data, line_index, map_lines,
                                   max_len) != 0)
    return (-1);
  if (validate_spaces(input_data, line_index, map_lines, max_len) != 0)
    return (-1);
  return (0);
}

/**
 * @brief マップセクションの構文を検証する（メモリ確保なし）
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @return 成功: 0 / 失敗: -1
 */
int validate_map(char **input_data, size_t line_index) {
  size_t map_lines;
  size_t max_len;

  if (!input_data)
    return (-1);
  while (input_data[line_index] && is_blank_line(input_data[line_index]))
    line_index++;
  if (!input_data[line_index])
    return (fprintf(stderr, "Error: Map not found after config\n"), -1);
  map_lines = count_map_lines(input_data, line_index);
  if (map_lines < MIN_MAP_SIZE)
    return (fprintf(stderr, "Error: Map must have at least %d lines\n",
                    MIN_MAP_SIZE),
            -1);
  max_len = get_max_line_length(input_data, line_index, map_lines);
  return (run_validations(input_data, line_index, map_lines, max_len));
}
