/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/27 00:35:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include "error_manage.h"
#include <stdlib.h>
#include <unistd.h>

static const char	*get_value_ptr(const char *line, t_identifier id)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (id >= ID_NO && id <= ID_EA)
		i += 2;
	else
		i += 1;
	while (ft_isspace(line[i]))
		i++;
	return (line + i);
}

static int	store_texture_path(t_identifier id, const char *line,
				t_config_data *config)
{
	char	*path;

	path = extract_texture_path(line, id);
	if (get_error_status() != 0)
		return (-1);
	if (!path)
		return (set_error_status(ERR_MALLOC_FAILURE), -1);
	if (access(path, R_OK) != 0)
		return (set_error_status(ERR_FILE_READ_PERMISSION), free(path), -1);
	if (id == ID_NO)
		config->north_texture_path = path;
	else if (id == ID_SO)
		config->south_texture_path = path;
	else if (id == ID_WE)
		config->west_texture_path = path;
	else if (id == ID_EA)
		config->east_texture_path = path;
	return (0);
}

static int	store_config_value(t_identifier id, const char *line,
				t_config_data *config)
{
	if (id >= ID_NO && id <= ID_EA)
	{
		store_texture_path(id, line, config);
		if (get_error_status() != 0)
			return (-1);
	}
	else if (id == ID_F)
	{
		parse_rgb_color(get_value_ptr(line, id), &config->floor_color);
		if (get_error_status() != 0)
			return (-1);
	}
	else if (id == ID_C)
	{
		parse_rgb_color(get_value_ptr(line, id), &config->ceiling_color);
		if (get_error_status() != 0)
			return (-1);
	}
	return (0);
}

static int	process_config_line(const char *line, t_config_data *config)
{
	t_identifier	id;

	id = detect_identifier(line);
	if (get_error_status() != 0)
		return (-1);
	if (id == ID_UNKNOWN)
		return (-1);
	store_config_value(id, line, config);
	if (get_error_status() != 0)
		return (-1);
	return (0);
}

int	load_config(const char **input_data, t_config_data *config)
{
	size_t	i;
	int		loaded_count;

	i = 0;
	loaded_count = 0;
	while (input_data[i] && loaded_count < 6)
	{
		if (is_blank_line(input_data[i]))
		{
			i++;
			continue ;
		}
		process_config_line(input_data[i], config);
		if (get_error_status() != 0)
			return (-1);
		loaded_count++;
		i++;
	}
	if (loaded_count != 6)
		return (-1);
	return (0);
}
