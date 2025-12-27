/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:39:26 by rnakatan          #+#    #+#             */
/*   Updated: 2025/11/24 11:04:24 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../includes/utils/utils.h"
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define READ_SIZE 1023
#define ERROR 1
#define SUCCESS 0

static int		append_char(char **line, size_t *len, size_t *cap, char c);
static int		append_line(char ***map, const char *line, size_t len);
static void		*free_and_return_error(char **map, char *line_buf);
static void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);

static int	g_line_count = 0;

const char	**read_map(const char *filename)
{
	const int	fd = open(filename, O_RDONLY);
	char		**map;
	char		buf[BUFFER_SIZE];
	char		*line_buf;
	size_t		line_len;
	size_t		line_cap;
	int			bytes_read;
	int			i;

	if (fd < 0)
		return (NULL);
	map = NULL;
	line_buf = NULL;
	line_len = 0;
	line_cap = 0;
	bytes_read = read(fd, buf, READ_SIZE);
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buf[i] == '\n')
			{
				if (line_len > 0 && line_buf[line_len - 1] == '\r')
					line_len--;
				if (append_line(&map, line_buf, line_len) == ERROR)
					return ((const char **)free_and_return_error(map, line_buf));
				line_len = 0;
			}
			else if (append_char(&line_buf, &line_len, &line_cap, buf[i]) == ERROR)
				return ((const char **)free_and_return_error(map, line_buf));
			i++;
		}
		bytes_read = read(fd, buf, READ_SIZE);
	}
	close(fd);
	if (bytes_read < 0)
		return ((const char **)free_and_return_error(map, line_buf));
	if (line_len > 0)
	{
		if (append_line(&map, line_buf, line_len) == ERROR)
			return ((const char **)free_and_return_error(map, line_buf));
	}
	free(line_buf);
	map = (char **)ft_realloc(map, sizeof(char *) * g_line_count,
			sizeof(char *) * (g_line_count + 1));
	if (map == NULL)
		return (NULL);
	map[g_line_count] = NULL;
	g_line_count = 0;
	return ((const char **)map);
}

static int	append_char(char **line, size_t *len, size_t *cap, char c)
{
	char	*tmp;

	if (*len + 1 >= *cap)
	{
		if (*cap == 0)
			*cap = 64;
		else
			*cap *= 2;
		tmp = malloc(*cap);
		if (tmp == NULL)
			return (ERROR);
		if (*line)
			ft_memcpy(tmp, *line, *len);
		free(*line);
		*line = tmp;
	}
	(*line)[*len] = c;
	(*len)++;
	return (SUCCESS);
}

static int	append_line(char ***map, const char *line, size_t len)
{
	char	*dup;

	*map = (char **)ft_realloc(*map, sizeof(char *) * g_line_count,
			sizeof(char *) * (g_line_count + 1));
	if (*map == NULL)
		return (ERROR);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (ERROR);
	if (len > 0)
		ft_memcpy(dup, line, len);
	dup[len] = '\0';
	(*map)[g_line_count] = dup;
	g_line_count++;
	return (SUCCESS);
}

static void	*free_and_return_error(char **map, char *line_buf)
{
	if (map != NULL)
	{
		map[g_line_count] = NULL;
		free_map((void **)map);
	}
	free(line_buf);
	g_line_count = 0;
	return (NULL);
}

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

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
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}
