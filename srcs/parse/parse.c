/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:19:59 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/09 15:51:24 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief メインのパース関数
 * @param filepath .cubファイルのパス
 * @param game_data パース結果を格納する構造体
 * @return 成功: 0 / 失敗: エラーコード
 */
int	parse(const char *filepath, t_game_data *game_data)
{
	char	**input_data;
	size_t	line_index;
	int		result;

	(void)filepath;
	(void)game_data;
	line_index = 0;
	input_data = NULL;
	// TODO: read_map()でファイルを読み込む
	// input_data = read_map(filepath);
	// if (input_data == NULL)
	//     return (-1);
	// result = parse_config(input_data, &line_index, &game_data->config);
	// if (result != 0)
	// 	return (result);
	// result = parse_map(input_data, line_index, &game_data->map);
	// if (result != 0)
	// 	return (result);
	// TODO: input_dataを解放
	(void)input_data;
	(void)line_index;
	(void)result;
	return (0);
}
