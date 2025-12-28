/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:39:26 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/28 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#define BUFFER_SIZE 4096

char		*duplicate_line(const char *start, const char *end);
char		*resize_buffer(char *old, int old_size, int new_size);
char		**resize_map(char **old, int old_size, int new_size);
const char	*process_line(char ***map, int *lines,
				const char *start, const char *end);
static char	*read_entire_file(int fd);
static char	**split_lines(const char *content, int *count);

const char	**read_map(const char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	char		*content;
	char		**map;

	if (fd < 0)
		return (NULL);
	content = read_entire_file(fd);
	close(fd);
	if (!content)
		return (NULL);
	map = split_lines(content, NULL);
	free(content);
	return ((const char **)map);
}

static char	*read_entire_file(int fd)
{
	char	*result;
	char	buf[BUFFER_SIZE + 1];
	int		total;
	int		bytes;

	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	total = 0;
	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		result = resize_buffer(result, total, total + bytes + 1);
		if (!result)
			return (NULL);
		ft_memcpy(result + total, buf, bytes + 1);
		total += bytes;
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes < 0)
		return (free(result), NULL);
	return (result);
}

static char	**split_lines(const char *content, int *count)
{
	char		**map;
	const char	*start;
	const char	*end;
	int			lines;

	lines = 0;
	map = NULL;
	start = content;
	while (*start)
	{
		end = start;
		while (*end && *end != '\n')
			end++;
		start = process_line(&map, &lines, start, end);
		if (!start)
			return (NULL);
	}
	map[lines] = NULL;
	if (count)
		*count = lines;
	return (map);
}
