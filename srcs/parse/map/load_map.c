/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 01:10:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/27 00:40:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdlib.h>

static size_t count_map_lines(char **input_data, size_t line_index) {
  size_t count;

  count = 0;
  while (input_data[line_index + count])
    count++;
  return (count);
}

static size_t get_max_line_length(char **input_data, size_t line_index,
                                  size_t map_lines) {
  size_t i;
  size_t max_len;
  size_t current_len;

  max_len = 0;
  i = 0;
  while (i < map_lines) {
    current_len = ft_strlen(input_data[line_index + i]);
    if (current_len > max_len)
      max_len = current_len;
    i++;
  }
  return (max_len);
}

static void free_partial_map(char **map, size_t count) {
  size_t i;

  i = 0;
  while (i < count) {
    free(map[i]);
    i++;
  }
  free(map);
}

static int copy_map_line(char *dest, const char *src, size_t max_len) {
  size_t j;
  size_t src_len;

  src_len = ft_strlen(src);
  j = 0;
  while (j < max_len) {
    if (j < src_len)
      dest[j] = src[j];
    else
      dest[j] = ' ';
    j++;
  }
  dest[max_len] = '\0';
  return (0);
}

int load_map(char **input_data, size_t line_index, t_map_data *map_data) {
  size_t map_lines;
  size_t max_len;
  size_t i;

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
  while (i < map_lines) {
    map_data->map[i] = malloc(sizeof(char) * (max_len + 1));
    if (!map_data->map[i])
      return (free_partial_map(map_data->map, i), -1);
    copy_map_line(map_data->map[i], input_data[line_index + i], max_len);
    i++;
  }
  map_data->map[map_lines] = NULL;
  return (0);
}
