/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:19:59 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/06 04:07:40 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief メインのパース関数
 * @param map 入力データ
 * @return 成功: 0 / 失敗: エラーコード
 */
int	parse(const char **map)
{
	t_game_data	game_data;
	size_t		line_index;
	int			result;

	line_index = 0;
	result = parse_config((char **)map, &line_index, &game_data.config);
	if (result != 0)
		return (result);
	result = parse_map((char **)map, line_index, &game_data.map);
	if (result != 0)
		return (result);
	return (0);
}
