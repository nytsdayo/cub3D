/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:19:59 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 04:29:45 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/* Utils function prototypes */
char **read_map(const char *filename);
void free_map(void **map);

/**
 * @brief メインのパース関数（検証のみ）
 * @param filepath .cubファイルのパス
 * @param game_data パース結果を格納する構造体（未使用、将来の拡張用）
 * @return 成功: 0 / 失敗: エラーコード
 */
int parse(const char *filepath, t_game_data *game_data) {
  char **input_data;
  size_t line_index;
  int result;

  (void)game_data;
  line_index = 0;
  input_data = read_map(filepath);
  if (input_data == NULL)
    return (-1);
  // result = validate_config(input_data, &line_index);
  // if (result != 0)
  // 	return (result);
  // result = validate_map(input_data, line_index);
  // if (result != 0)
  // 	return (result);
  free_map((void **)input_data);
  (void)filepath;
  (void)input_data;
  (void)line_index;
  (void)result;
  return (0);
}
