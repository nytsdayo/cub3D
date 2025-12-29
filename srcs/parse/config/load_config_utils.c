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
#include <stdlib.h>

char	*extract_texture_path(const char *line, t_identifier id)
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

int	parse_rgb_color(const char *line, t_rgb *color)
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
