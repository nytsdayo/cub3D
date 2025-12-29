/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/20 12:37:48 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include "error_manage.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/* External function prototypes (from validate_format.c) */
int			validate_texture_format(const char *line, t_identifier id);
int			validate_rgb_format(const char *line);

/* Static function prototypes */

static void	init_seen_flags(t_seen_flags seen_flags);
static bool	all_identifiers_found(t_seen_flags seen_flags);
static int	validate_identifier_line(const char *line,
				t_seen_flags seen_flags, t_identifier id);
static int	get_identifier_index(t_identifier id);

/* Main function */

/**
 * @brief 設定セクションの構文を検証する（値の確保は行わない）
 */
int	validate_config(char **input_data, size_t *line_index)
{
	t_seen_flags	seen_flags;
	t_identifier	id;

	init_seen_flags(seen_flags);
	while (input_data[*line_index] != NULL
		&& !all_identifiers_found(seen_flags))
	{
		if (is_blank_line(input_data[*line_index]))
		{
			(*line_index)++;
			continue ;
		}
		id = detect_identifier(input_data[*line_index]);
		if (id == ID_UNKNOWN)
			return (set_error_status(ERR_UNKNOWN_IDENTIFIER), -1);
		validate_identifier_line(input_data[*line_index],
				seen_flags, id);
		if (get_error_status() != 0)
			return (-1);
		(*line_index)++;
	}
	if (!all_identifiers_found(seen_flags))
		return (set_error_status(ERR_MISSING_IDENTIFIER), -1);
	return (0);
}

/* Static function implementations */

static void	init_seen_flags(t_seen_flags seen_flags)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		seen_flags[i] = 0;
		i++;
	}
}

static int	get_identifier_index(t_identifier id)
{
	if (id == ID_NO)
		return (0);
	else if (id == ID_SO)
		return (1);
	else if (id == ID_WE)
		return (2);
	else if (id == ID_EA)
		return (3);
	else if (id == ID_F)
		return (4);
	else if (id == ID_C)
		return (5);
	return (-1);
}

static bool	all_identifiers_found(t_seen_flags seen_flags)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (seen_flags[i] == 0)
			return (false);
		i++;
	}
	return (true);
}

static int	validate_identifier_line(const char *line,
		t_seen_flags seen_flags, t_identifier id)
{
	int	idx;

	idx = get_identifier_index(id);
	if (seen_flags[idx] > 0)
		return (set_error_status(ERR_DUPLICATE_IDENTIFIER), -1);
	while (ft_isspace(*line))
		line++;
	if (id >= ID_NO && id <= ID_EA)
	{
		validate_texture_format(line + 2, id);
		if (get_error_status() != 0)
			return (-1);
	}
	else
	{
		validate_rgb_format(line + 1);
		if (get_error_status() != 0)
			return (-1);
	}
	seen_flags[idx]++;
	return (0);
}
