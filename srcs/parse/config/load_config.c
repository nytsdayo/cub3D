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
#include <stdlib.h>
#include <unistd.h>

static char	*extract_texture_path(const char *line, t_identifier id)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	if (id >= ID_NO && id <= ID_EA)
		i += 2;
	else
		i += 1;
	while (ft_isspace(line[i]))
		i++;
	start = i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '\n')
		i++;
	len = i - start;
	return (ft_strndup(&line[start], len));
}

static int	parse_rgb_component(const char *str, int *idx)
{
	int	value;
	int	digits;

	value = 0;
	digits = 0;
	while (ft_isdigit(str[*idx]) && digits < 3)
	{
		value = value * 10 + (str[*idx] - '0');
		(*idx)++;
		digits++;
	}
	if (digits == NON_NUM || value > RGB_MAX)
		return (-1);
	return (value);
}

static int	parse_rgb_color(const char *line, t_color *color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	r = parse_rgb_component(line, &i);
	if (r == -1 || line[i++] != ',')
		return (-1);
	g = parse_rgb_component(line, &i);
	if (g == -1 || line[i++] != ',')
		return (-1);
	b = parse_rgb_component(line, &i);
	if (b == -1)
		return (-1);
	color->r = r;
	color->g = g;
	color->b = b;
	return (0);
}

static int	store_config_value(t_identifier id, const char *line,
				t_config_data *config)
{
	char	*path;

	if (id == ID_NO)
	{
		path = extract_texture_path(line, id);
		if (!path || access(path, R_OK) != 0)
			return (free(path), -1);
		config->north_texture_path = path;
	}
	else if (id == ID_SO)
	{
		path = extract_texture_path(line, id);
		if (!path || access(path, R_OK) != 0)
			return (free(path), -1);
		config->south_texture_path = path;
	}
	else if (id == ID_WE)
	{
		path = extract_texture_path(line, id);
		if (!path || access(path, R_OK) != 0)
			return (free(path), -1);
		config->west_texture_path = path;
	}
	else if (id == ID_EA)
	{
		path = extract_texture_path(line, id);
		if (!path || access(path, R_OK) != 0)
			return (free(path), -1);
		config->east_texture_path = path;
	}
	else if (id == ID_F)
		return (parse_rgb_color(line + 1, &config->floor_color));
	else if (id == ID_C)
		return (parse_rgb_color(line + 1, &config->ceiling_color));
	return (0);
}

int	load_config(const char **input_data, t_config_data *config)
{
	size_t			i;
	int				loaded_count;
	t_identifier	id;

	i = 0;
	loaded_count = 0;
	while (input_data[i] && loaded_count < 6)
	{
		if (is_blank_line(input_data[i]))
		{
			i++;
			continue ;
		}
		id = detect_identifier(input_data[i]);
		if (id == ID_UNKNOWN)
			return (-1);
		if (store_config_value(id, input_data[i], config) != 0)
			return (-1);
		loaded_count++;
		i++;
	}
	if (loaded_count != 6)
		return (-1);
	return (0);
}
