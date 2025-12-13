/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 20:10:28 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/* Static function prototypes */

/**
 * @brief 行の先頭から識別子を検出する
 */
static t_identifier	detect_identifier(const char *line);

/**
 * @brief 識別子のインデックスを取得する
 */
/**
 * @brief seen_flagsを初期化する
 */
static void			init_seen_flags(t_seen_flags seen_flags);

/**
 * @brief テクスチャパスのフォーマットを検証する（.xpm拡張子チェック）
 */
static int			validate_texture_format(const char *line, t_identifier id);

/**
 * @brief RGB値のフォーマットを検証する（R,G,B形式、0-255範囲チェック）
 */
static int			validate_rgb_format(const char *line);

/**
 * @brief すべての識別子が1回ずつ見つかったかを確認する
 */
static bool			all_identifiers_found(t_seen_flags seen_flags);

/**
 * @brief 識別子の行を検証する
 */
static int			validate_identifier_line(const char *line,
						t_seen_flags seen_flags, t_identifier id);

/**
 * @brief 識別子のインデックスを取得する
 */
static int			get_identifier_index(t_identifier id);

/**
 * @brief seen_flagsを初期化する
 */
static void			init_seen_flags(t_seen_flags seen_flags);

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
			return (write(2, "Error\nUnknown identifier\n", 25), -1);
		result = validate_identifier_line(input_data[*line_index],
				seen_flags, id);
		if (result != 0)
			return (result);
		(*line_index)++;
	}
	if (!all_identifiers_found(seen_flags))
		return (write(2, "Error\nMissing identifier\n", 25), -1);
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

static t_identifier	detect_identifier(const char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && ft_isspace(line[i + 2]))
		return (ID_NO);
	if (ft_strncmp(&line[i], "SO", 2) == 0 && ft_isspace(line[i + 2]))
		return (ID_SO);
	if (ft_strncmp(&line[i], "WE", 2) == 0 && ft_isspace(line[i + 2]))
		return (ID_WE);
	if (ft_strncmp(&line[i], "EA", 2) == 0 && ft_isspace(line[i + 2]))
		return (ID_EA);
	if (line[i] == 'F' && ft_isspace(line[i + 1]))
		return (ID_F);
	if (line[i] == 'C' && ft_isspace(line[i + 1]))
		return (ID_C);
	return (ID_UNKNOWN);
}

static int	validate_texture_format(const char *line, t_identifier id)
{
	int	i;
	int	start;
	int	len;

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
	if (len < 4 || ft_strncmp(&line[start + len - 4], ".xpm", 4) != 0)
		return (-1);
	return (0);
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

static int	validate_rgb_format(const char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (parse_rgb_component(line, &i) == -1 || line[i++] != ','
		|| parse_rgb_component(line, &i) == -1 || line[i++] != ','
		|| parse_rgb_component(line, &i) == -1)
		return (-1);
	return (0);
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
		return (write(2, "Error\nDuplicate identifier\n", 27), -1);
	while (ft_isspace(*line))
		line++;
	if (id >= ID_NO && id <= ID_EA)
	{
		if (validate_texture_format(line + 2, id) != 0)
			return (write(2, "Error\nInvalid texture path\n", 27), -1);
	}
	else
	{
		if (validate_rgb_format(line + 1) != 0)
			return (write(2, "Error\nInvalid RGB value\n", 24), -1);
	}
	seen_flags[idx]++;
	return (0);
}
