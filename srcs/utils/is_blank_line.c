/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_blank_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdbool.h>

/**
 * @brief 空白のみの行かどうかを判定する
 * @param line 判定する行
 * @return true: 空白のみ / false: それ以外
 */
int is_blank_line(const char *line) {
  int i;

  i = 0;
  while (line[i]) {
    if (!ft_isspace(line[i]) && line[i] != '\n')
      return (0);
    i++;
  }
  return (1);
}
