/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:29:11 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 22:58:29 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>
# include <stdbool.h>
# include "cub3d.h"
# include "error_manage.h"

# define RGB_MAX 255
# define NON_NUM 0

typedef enum e_identifier
{
	ID_UNKNOWN,
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_F,
	ID_C
}	t_identifier;

typedef int	t_seen_flags[6];

typedef struct s_config_data
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	t_rgb	floor_color;
	t_rgb	ceiling_color;
}	t_config_data;

typedef struct s_map_data
{
	char	**map;
}	t_map_data;

typedef struct s_game_data
{
	t_config_data	config;
	t_map_data		map;
}	t_game_data;

typedef struct s_space_check_ctx
{
	char	**input_data;
	size_t	line_index;
	size_t	map_lines;
}	t_space_check_ctx;

int				parse(const char *filepath, t_game_data *game_data);
int				validate_config(char **input_data, size_t *line_index);
/**
 * @brief 行の先頭から識別子を検出する
 */
t_identifier	detect_identifier(const char *line);
int				validate_map(char **input_data, size_t line_index);

int				load_data(const char **input_data, void *data);
int				load_config(const char **input_data, t_config_data *config);
int				load_map(char **input_data, size_t line_index,
					t_map_data *map_data);

char			*extract_texture_path(const char *line, t_identifier id);
int				parse_rgb_component(const char *str, int *idx);
int				parse_rgb_color(const char *line, t_rgb *color);

bool			is_valid_char(char c);
size_t			count_map_lines(char **input_data, size_t line_index);
size_t			get_max_line_length(char **input_data, size_t line_index,
					size_t map_lines);
char			get_char_at(char **input_data, size_t line_index,
					size_t row, size_t col);
int				validate_map_size(char **input_data, size_t line_index,
					size_t map_lines, size_t max_len);
int				validate_player_start(char **input_data, size_t line_index,
					size_t map_lines);
int				validate_invalid_chars(char **input_data, size_t line_index,
					size_t map_lines);
int				validate_surrounded_by_walls(char **input_data,
					size_t line_index, size_t map_lines, size_t max_len);
int				validate_spaces(char **input_data, size_t line_index,
					size_t map_lines, size_t max_len);

const char		*process_line(char ***map, int *lines,
					const char *start, const char *end);

#endif
