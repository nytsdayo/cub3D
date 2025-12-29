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
	int				result;

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
		{
			error_msg("Error\nUnknown identifier\n");
			set_error_status(ERR_UNKNOWN_IDENTIFIER);
			return (-1);
		}
		result = validate_identifier_line(input_data[*line_index],
				seen_flags, id);
		if (result != 0)
			return (result);
		(*line_index)++;
	}
	if (!all_identifiers_found(seen_flags))
	{
		error_msg("Error\nMissing identifier\n");
		set_error_status(ERR_MISSING_IDENTIFIER);
		return (-1);
	}
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
	{
		error_msg("Error\nDuplicate identifier\n");
		set_error_status(ERR_DUPLICATE_IDENTIFIER);
		return (-1);
	}
	while (ft_isspace(*line))
		line++;
	if (id >= ID_NO && id <= ID_EA)
	{
		if (validate_texture_format(line + 2, id) != 0)
		{
			error_msg("Error\nInvalid texture path\n");
			set_error_status(ERR_SYNTAX_TEXTURE);
			return (-1);
		}
	}
	else
	{
		if (validate_rgb_format(line + 1) != 0)
		{
			error_msg("Error\nInvalid RGB value\n");
			set_error_status(ERR_SYNTAX_RGB);
			return (-1);
		}
	}
	seen_flags[idx]++;
	return (0);
}
