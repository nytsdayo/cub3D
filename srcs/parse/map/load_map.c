/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 01:10:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/20 01:16:18 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdlib.h>

/**
 * @brief マップセクションをメモリに読み込む
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_data マップデータを格納する構造体
 * @return 成功: 0 / 失敗: -1
 */
int	load_map(char **input_data, size_t line_index, t_map_data *map_data)
{
	(void)input_data;
	(void)line_index;
	(void)map_data;
	return (0);
}

// /**
//  * @brief マップデータをメモリに読み込む
//  * @param input_data 入力データの行配列
//  * @param line_index マップの開始行インデックス
//  * @param map_data マップデータを格納する構造体
//  * @return 成功: 0 / 失敗: -1
//  */
// int	load_map(char **input_data, size_t line_index, t_map_data *map_data)
// {
// 	size_t	map_lines;
// 	size_t	max_len;
// 	size_t	i;
// 	size_t	j;

// 	if (!input_data || !map_data)
// 		return (-1);
// 	if (validate_map(input_data, line_index) != 0)
// 		return (-1);
// 	map_lines = count_map_lines(input_data, line_index);
// 	max_len = get_max_line_length(input_data, line_index, map_lines);
// 	map_data->map = malloc(sizeof(char *) * (map_lines + 1));
// 	if (!map_data->map)
// 		return (-1);
// 	i = 0;
// 	while (i < map_lines)
// 	{
// 		map_data->map[i] = calloc(max_len + 1, sizeof(char));
// 		if (!map_data->map[i])
// 		{
// 			while (i > 0)
// 				free(map_data->map[--i]);
// 			free(map_data->map);
// 			map_data->map = NULL;
// 			return (-1);
// 		}
// 		j = 0;
// 		while (j < max_len)
// 		{
// 			if (j < ft_strlen(input_data[line_index + i]))
// 				map_data->map[i][j] = input_data[line_index + i][j];
// 			else
// 				map_data->map[i][j] = ' ';
// 			j++;
// 		}
// 		map_data->map[i][max_len] = '\0';
// 		i++;
// 	}
// 	map_data->map[map_lines] = NULL;
// 	return (0);
// }
