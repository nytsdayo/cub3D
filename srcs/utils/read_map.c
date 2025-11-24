/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:39:26 by rnakatan          #+#    #+#             */
/*   Updated: 2025/11/24 10:57:28 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../includes/utils/utils.h"
#include <fcntl.h>

static int	process_buffer_lines(char ***map, char *buf);
static void	*free_and_return_error(char **map);
static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

static int	g_bytes_read;
static int	g_line_count = 0;

const char	**read_map(const char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	char		**map;
	char		buf[1024];

	if (fd < 0)
		return (NULL);
	map = NULL;
	g_bytes_read = read(fd, buf, 1023);
	while (g_bytes_read > 0)
	{
		if (process_buffer_lines(&map, buf) == 1)
			return ((const char **)free_and_return_error(map));
		g_bytes_read = read(fd, buf, 1023);
	}
	close(fd);
	if (g_bytes_read < 0)
		return ((const char **)free_and_return_error(map));
	map = (char **)ft_realloc(map, sizeof(char *) * g_line_count,
			sizeof(char *) * (g_line_count + 1));
	if (map == NULL)
		return (NULL);
	map[g_line_count] = NULL;
	g_line_count = 0;
	return ((const char **)map);
}

static int	process_buffer_lines(char ***map, char *buf)
{
	int	i;
	int	line_start;

	buf[g_bytes_read] = '\0';
	i = 0;
	line_start = 0;
	while (i < g_bytes_read)
	{
		if (buf[i] == '\n')
		{
			*map = (char **)ft_realloc(*map, sizeof(char *) * g_line_count,
					sizeof(char *) * (g_line_count + 1));
			if (*map == NULL)
				return (1);
			(*map)[g_line_count] = ft_strndup(&buf[line_start],
					i - line_start);
			if ((*map)[g_line_count] == NULL)
				return (1);
			g_line_count++;
			line_start = i + 1;
		}
		i++;
	}
	return (0);
}

static void	*free_and_return_error(char **map)
{
	if (map != NULL)
	{
		map[g_line_count] = NULL;
		free_map((void **)map);
	}
	g_line_count = 0;
	return (NULL);
}

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;
	size_t	i;

	if (new_size == 0)
		return (free(ptr), NULL);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
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
