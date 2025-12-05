/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:29:11 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/06 04:07:40 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stddef.h>

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

/* 公開関数 */

int	parse(const char **map);
int	parse_config(char **input_data, size_t *line_index,
		t_config_data *config);
int	parse_map(char **input_data, size_t line_index, t_map_data *map_data);

#endif