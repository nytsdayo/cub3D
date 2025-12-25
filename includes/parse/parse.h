/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:29:11 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/20 01:24:22 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>

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

/* データ構造 */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_config_data
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	t_color	floor_color;
	t_color	ceiling_color;
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

int				parse(const char *filepath, t_game_data *game_data);
int				validate_config(char **input_data, size_t *line_index);
/**
 * @brief 行の先頭から識別子を検出する
 */
t_identifier	detect_identifier(const char *line);
int				validate_map(char **input_data, size_t line_index);

int				load_data(const char **input_data, void *data);
int				load_config(const char *filepath, t_config_data *config);
int				load_map(char **input_data, size_t line_index,
					t_map_data *map_data);

#endif
