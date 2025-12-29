/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:21:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/27 00:21:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

/**
 * @brief テクスチャパスのフォーマットを検証する（.xpm拡張子チェック）
 */
int validate_texture_format(const char *line, t_identifier id) {
  int i;
  int start;
  int len;

  i = 0;
  if (id >= ID_NO && id <= ID_EA)
    i += 2;
  else
    i += 1;
  while (ft_isspace(line[i]))
    i++;
  start = i;
  while (line[i] && !ft_isspace(line[i]) && line[i] != '\n')
    i++;
  len = i - start;
  if (len < 4)
    return (set_error_status(ERR_INVALID_FILE_EXTENSION), -1);
  if (ft_strncmp(&line[start + len - 4], ".xpm", 4) != 0)
    return (set_error_status(ERR_INVALID_FILE_EXTENSION), -1);
  return (0);
}

static int parse_component_with_spaces(const char *line, int *idx) {
  int value;

  while (ft_isspace(line[*idx]))
    (*idx)++;
  value = parse_rgb_component(line, idx);
  if (value < 0)
    return (set_error_status(ERR_SYNTAX_RGB), -1);
  while (ft_isspace(line[*idx]))
    (*idx)++;
  return (value);
}

static int expect_comma(const char *line, int *idx) {
  if (line[*idx] != ',')
    return (set_error_status(ERR_SYNTAX_RGB), -1);
  (*idx)++;
  return (0);
}

/**
 * @brief RGB値のフォーマットを検証する（R,G,B形式、0-255範囲チェック）
 *        数値やカンマの前後に空白があっても許容する
 */
int validate_rgb_format(const char *line) {
  int i;

  i = 0;
  if (parse_component_with_spaces(line, &i) < 0 || expect_comma(line, &i) < 0 ||
      parse_component_with_spaces(line, &i) < 0 || expect_comma(line, &i) < 0 ||
      parse_component_with_spaces(line, &i) < 0)
    return (-1);
  while (ft_isspace(line[i]))
    i++;
  if (line[i] != '\0')
    return (set_error_status(ERR_SYNTAX_RGB), -1);
  return (0);
}
