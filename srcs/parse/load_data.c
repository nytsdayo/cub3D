/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 01:06:30 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/27 00:45:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>

int load_data(const char **input_data, void *data) {
  t_game_data *game_data;
  size_t line_index;

  game_data = (t_game_data *)data;
  line_index = 0;
  if (load_config(input_data, &game_data->config) != 0)
    return (-1);
  while (input_data[line_index]) {
    if (detect_identifier(input_data[line_index]) == ID_UNKNOWN)
      break;
    line_index++;
  }
  if (load_map((char **)input_data, line_index, &game_data->map) != 0)
    return (-1);
  return (0);
}
