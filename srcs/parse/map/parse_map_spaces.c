/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 22:42:07 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>

static int	check_space_cell(const t_space_check_ctx *ctx,
				size_t i, size_t j);
static int	check_all_adjacent(const t_space_check_ctx *ctx,
				size_t i, size_t j);

/**
 * @brief スペースが無効な位置にないことを検証する
 * @param input_data 入力データの行配列
 * @param line_index マップの開始行インデックス
 * @param map_lines マップの行数
 * @param max_len 最大行長
 * @return 成功: 0 / 失敗: -1
 */
int	validate_spaces(char **input_data, size_t line_index,
		size_t map_lines, size_t max_len_param)
{
	size_t				i;
	size_t				j;
	t_space_check_ctx	ctx;

	ctx.input_data = input_data;
	ctx.line_index = line_index;
	ctx.map_lines = map_lines;
	i = 0;
	while (i < map_lines)
	{
		j = 0;
		while (j < max_len_param)
		{
			if (check_space_cell(&ctx, i, j) != 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_space_cell(const t_space_check_ctx *ctx,
		size_t i, size_t j)
{
	char	c;

	c = get_char_at(ctx->input_data, ctx->line_index, i, j);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (check_all_adjacent(ctx, i, j) != 0)
			return (-1);
	}
	return (0);
}

static int	check_dir(const t_space_check_ctx *ctx, size_t i, size_t j)
{
	size_t	row_len;
	char	adj;

	if (i >= ctx->map_lines)
		return (set_error_status(ERR_SPACE_VOID_CONTACT), -1);
	row_len = ft_strlen(ctx->input_data[ctx->line_index + i]);
	if (j >= row_len)
		return (set_error_status(ERR_SPACE_VOID_CONTACT), -1);
	adj = ctx->input_data[ctx->line_index + i][j];
	if (adj == ' ')
		return (set_error_status(ERR_SPACE_VOID_CONTACT), -1);
	return (0);
}

static int	check_all_adjacent(const t_space_check_ctx *ctx,
		size_t i, size_t j)
{
	if (i > 0 && check_dir(ctx, i - 1, j) != 0)
		return (-1);
	if (j > 0 && check_dir(ctx, i, j - 1) != 0)
		return (-1);
	if (check_dir(ctx, i + 1, j) != 0)
		return (-1);
	if (check_dir(ctx, i, j + 1) != 0)
		return (-1);
	return (0);
}
