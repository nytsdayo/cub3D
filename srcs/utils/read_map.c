/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:39:26 by rnakatan          #+#    #+#             */
/*   Updated: 2025/11/24 08:21:38 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../includes/utils/utils.h"
#include <fcntl.h>

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
static char	*ft_strdup_len(const char *s, size_t len);
static int	process_buffer_lines(char ***map, char *buf,
						int bytes_read, int *line_count);

const char	**read_map(const char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	char		**map;
	char		buf[1024];
	int			bytes_read;
	int			line_count;

	if (fd < 0)
		return (NULL);
	map = NULL;
	line_count = 0;
	bytes_read = read(fd, buf, 1023);
	while (bytes_read > 0)
	{
		if (process_buffer_lines(&map, buf, bytes_read, &line_count) == 1)
		{
			if (map != NULL)
			{
				map[line_count] = NULL;
				free_map((void **)map);
			}
			return (NULL);
		}
		bytes_read = read(fd, buf, 1023);
	}
	close(fd);
	if (bytes_read < 0)
	{
		if (map != NULL)
		{
			map[line_count] = NULL;
			free_map((void **)map);
		}
		return (NULL);
	}
	map = (char **)ft_realloc(map, sizeof(char *) * line_count,
			sizeof(char *) * (line_count + 1));
	if (map == NULL)
		return (NULL);
	map[line_count] = NULL;
	return ((const char **)map);
}

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;
	size_t	i;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		copy_size = old_size < new_size ? old_size : new_size;
		i = 0;
		while (i < copy_size)
		{
			((char *)new_ptr)[i] = ((char *)ptr)[i];
			i++;
		}
		free(ptr);
	}
	return (new_ptr);
}

static char	*ft_strdup_len(const char *s, size_t len)
{
	char	*dst;
	size_t	i;

	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	process_buffer_lines(char ***map, char *buf,
						int bytes_read, int *line_count)
{
	int	i;
	int	line_start;

	buf[bytes_read] = '\0';
	i = 0;
	line_start = 0;
	while (i < bytes_read)
	{
		if (buf[i] == '\n')
		{
			*map = (char **)ft_realloc(*map, sizeof(char *)
					* (*line_count), sizeof(char *) * (*line_count + 1));
			if (*map == NULL)
				return (1);
			(*map)[*line_count] = ft_strdup_len(&buf[line_start], i - line_start);
			if ((*map)[*line_count] == NULL)
				return (1);
			(*line_count)++;
			line_start = i + 1;
		}
		i++;
	}
	return (0);
}
