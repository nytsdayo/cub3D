/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:19:59 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 22:19:26 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "error_manage.h"
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
  int ret;

  line_index = 0;
  input_data = read_map(filepath);
  if (get_error_status() != 0)
    return (-1);
  validate_config(input_data, &line_index);
  if (get_error_status() != 0) {
    free_map((void **)input_data);
    return (-1);
  }
  validate_map(input_data, line_index);
  if (get_error_status() != 0) {
    free_map((void **)input_data);
    return (-1);
  }
  ret = load_data((const char **)input_data, game_data);
  free_map((void **)input_data);
  if (get_error_status() != 0)
    return (-1);
  return (ret);
}
