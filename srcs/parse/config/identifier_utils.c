/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdbool.h>

/**
 * @brief 空白のみの行かどうかを判定する
 */
bool	is_blank_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief 行の先頭から識別子を検出する
 */
t_identifier	detect_identifier(const char *line)
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

/**
 * @brief 識別子のインデックスを取得する
 */
int	get_identifier_index(t_identifier id)
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

/**
 * @brief すべての識別子が1回ずつ見つかったかを確認する
 */
bool	all_identifiers_found(t_seen_flags seen_flags)
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

/**
 * @brief seen_flagsを初期化する
 */
void	init_seen_flags(t_seen_flags seen_flags)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		seen_flags[i] = 0;
		i++;
	}
}
