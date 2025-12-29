/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manage.h"
#include <stddef.h>

static const char	*get_parse_error(t_error_code code)
{
	if (code == ERR_UNKNOWN_IDENTIFIER)
		return ("Unknown identifier in config section");
	if (code == ERR_DUPLICATE_IDENTIFIER)
		return ("Duplicate identifier found");
	if (code == ERR_SYNTAX_TEXTURE)
		return ("Invalid texture path syntax");
	if (code == ERR_SYNTAX_RGB)
		return ("Invalid RGB color format or range");
	if (code == ERR_MISSING_IDENTIFIER)
		return ("Missing required identifier");
	return (NULL);
}

static const char	*get_map_error(t_error_code code)
{
	if (code == ERR_CONFIG_AFTER_MAP)
		return ("Config line appeared after map section");
	if (code == ERR_MINIMUM_MAP_SIZE)
		return ("Map is too small (minimum 3x3 required)");
	if (code == ERR_MAXIMUM_MAP_SIZE)
		return ("Map exceeds maximum allowed size");
	if (code == ERR_WALL_ENCLOSURE)
		return ("Map is not enclosed by walls");
	if (code == ERR_PLAYER_COUNT_ZERO)
		return ("No player start position found");
	if (code == ERR_PLAYER_COUNT_MULTIPLE)
		return ("Multiple player start positions found");
	if (code == ERR_ROW_LENGTH_INCONSISTENT)
		return ("Inconsistent row lengths in map");
	if (code == ERR_INVALID_CHARACTER)
		return ("Invalid character in map");
	if (code == ERR_SPACE_VOID_CONTACT)
		return ("Space character touches void area");
	return (NULL);
}

static const char	*get_system_error(t_error_code code)
{
	if (code == ERR_FILE_NOT_FOUND)
		return ("File not found");
	if (code == ERR_FILE_READ_PERMISSION)
		return ("Permission denied reading file");
	if (code == ERR_INVALID_FILE_EXTENSION)
		return ("Invalid file extension");
	if (code == ERR_INVALID_PATH)
		return ("Invalid file path");
	if (code == ERR_MALLOC_FAILURE)
		return ("Memory allocation failed");
	if (code == ERR_BUFFER_OVERFLOW)
		return ("Buffer overflow detected");
	return (NULL);
}

static const char	*get_engine_error(t_error_code code)
{
	if (code == ERR_MLX_INIT_FAILURE)
		return ("Failed to initialize MLX");
	if (code == ERR_WINDOW_CREATION_FAILURE)
		return ("Failed to create window");
	if (code == ERR_IMAGE_CREATION_FAILURE)
		return ("Failed to create image");
	if (code == ERR_TEXTURE_LOAD_FAILURE)
		return ("Failed to load texture");
	if (code == ERR_DDA_OUT_OF_BOUNDS)
		return ("DDA algorithm accessed out of bounds");
	if (code == ERR_DRAW_COORD_OUT_OF_RANGE)
		return ("Drawing coordinate out of range");
	return (NULL);
}

const char	*get_error_message(t_error_code code)
{
	const char	*msg;

	if (code == ERR_INVALID_ARGC)
		return ("Usage: ./cub3D <map.cub>");
	if (code == ERR_INVALID_ARGV)
		return ("Invalid argument");
	msg = get_parse_error(code);
	if (msg)
		return (msg);
	msg = get_map_error(code);
	if (msg)
		return (msg);
	msg = get_system_error(code);
	if (msg)
		return (msg);
	msg = get_engine_error(code);
	if (msg)
		return (msg);
	return ("An error occurred");
}
