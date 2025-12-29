/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/28 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include "error_manage.h"
#include <stdlib.h>

static int	skip_to_value_start(const char *line, t_identifier id)
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
	return (i);
}

static int	parse_component_with_spaces(const char *line, int *idx)
{
	int	value;

	while (ft_isspace(line[*idx]))
		(*idx)++;
	value = parse_rgb_component(line, idx);
	if (value < 0)
		return (-1);
	while (ft_isspace(line[*idx]))
		(*idx)++;
	return (value);
}

static int	expect_comma(const char *line, int *idx)
{
	if (line[*idx] != ',')
		return (-1);
	(*idx)++;
	return (0);
}

char	*extract_texture_path(const char *line, t_identifier id)
{
	int		i;
	int		start;
	int		len;

	i = skip_to_value_start(line, id);
	start = i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '\n')
		i++;
	len = i - start;
	return (ft_strndup(&line[start], len));
}

int	parse_rgb_component(const char *str, int *idx)
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

int	parse_rgb_color(const char *line, t_color *color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = parse_component_with_spaces(line, &i);
	if (r == -1 || expect_comma(line, &i) != 0)
		return (set_error_status(ERR_SYNTAX_RGB), -1);
	g = parse_component_with_spaces(line, &i);
	if (g == -1 || expect_comma(line, &i) != 0)
		return (set_error_status(ERR_SYNTAX_RGB), -1);
	b = parse_component_with_spaces(line, &i);
	if (b == -1)
		return (set_error_status(ERR_SYNTAX_RGB), -1);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\0')
		return (set_error_status(ERR_SYNTAX_RGB), -1);
	color->r = r;
	color->g = g;
	color->b = b;
	return (0);
}
