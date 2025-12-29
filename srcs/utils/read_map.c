/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:39:26 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 22:43:45 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manage.h"
#include "utils.h"

#define BUFFER_SIZE 4096

static char *read_entire_file(int fd);
static char **split_lines(const char *content, int *count);

const char **read_map(const char *filename) {
  const int fd = open(filename, O_RDONLY);
  char *content;
  char **map;

  if (fd < 0)
    return (set_error_status(ERR_FILE_NOT_FOUND), NULL);
  content = read_entire_file(fd);
  close(fd);
  if (!content)
    return (NULL);
  if (get_error_status() != 0)
    return (NULL);
  map = split_lines(content, NULL);
  free(content);
  if (get_error_status() != 0)
    return (NULL);
  return ((const char **)map);
}

static char *read_entire_file(int fd) {
  char *result;
  char buf[BUFFER_SIZE + 1];
  int total;
  int bytes;

  result = malloc(1);
  if (!result)
    return (set_error_status(ERR_MALLOC_FAILURE), NULL);
  result[0] = '\0';
  total = 0;
  bytes = read(fd, buf, BUFFER_SIZE);
  while (bytes > 0) {
    buf[bytes] = '\0';
    result = resize_buffer(result, total, total + bytes + 1);
    if (!result)
      return (NULL);
    ft_memcpy(result + total, buf, bytes + 1);
    total += bytes;
    bytes = read(fd, buf, BUFFER_SIZE);
  }
  if (bytes < 0)
    return (set_error_status(ERR_FILE_READ_PERMISSION), free(result), NULL);
  return (result);
}

static char **split_lines(const char *content, int *count) {
  char **map;
  const char *start;
  const char *end;
  int lines;

  lines = 0;
  map = NULL;
  start = content;
  while (*start) {
    end = start;
    while (*end && *end != '\n')
      end++;
    start = process_line(&map, &lines, start, end);
    if (!start)
      return (NULL);
    if (get_error_status() != 0)
      return (NULL);
  }
  if (!map)
    return (set_error_status(ERR_FILE_READ_PERMISSION), NULL);
  map[lines] = NULL;
  if (count)
    *count = lines;
  return (map);
}
