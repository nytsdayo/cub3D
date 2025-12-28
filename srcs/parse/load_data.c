/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 01:06:30 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/28 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdlib.h>

static int	skip_config_lines(const char **input_data, size_t *line_index);
static int	process_line(const char *line, size_t *id_count, int *done);

int	load_data(const char **input_data, void *data)
{
	t_game_data	*game_data;
	size_t		line_index;

	game_data = (t_game_data *)data;
	if (load_config(input_data, &game_data->config) != 0)
		return (-1);
	line_index = 0;
	if (skip_config_lines(input_data, &line_index) != 0)
		return (write(2, "Error\n", 6), -1);
	if (load_map((char **)input_data, line_index, &game_data->map) != 0)
		return (-1);
	return (0);
}

static int	skip_config_lines(const char **input_data, size_t *line_index)
{
	size_t	id_count;
	int		done;

	id_count = 0;
	done = 0;
	while (input_data[*line_index] && !done)
	{
		if (process_line(input_data[*line_index], &id_count, &done) != 0)
			return (-1);
		if (!done)
			(*line_index)++;
	}
	if (id_count < 6)
		return (-1);
	return (0);
}

static int	process_line(const char *line, size_t *id_count, int *done)
{
	t_identifier	id;

	if (is_blank_line(line))
		return (0);
	id = detect_identifier(line);
	if (id != ID_UNKNOWN)
	{
		if (*id_count >= 6)
			return (-1);
		(*id_count)++;
		return (0);
	}
	if (*id_count < 6)
		return (-1);
	*done = 1;
	return (0);
}
