/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:21:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/27 00:21:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

/**
 * @brief テクスチャパスのフォーマットを検証する（.xpm拡張子チェック）
 */
int	validate_texture_format(const char *line, t_identifier id)
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
	if (len < 4)
		return (-1);
	if (ft_strncmp(&line[start + len - 4], ".xpm", 4) != 0)
		return (-1);
	return (0);
}

/**
 * @brief RGB成分をパースする
 */
int	parse_rgb_component(const char *str, int *idx)
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

/**
 * @brief RGB値のフォーマットを検証する（R,G,B形式、0-255範囲チェック）
 */
int	validate_rgb_format(const char *line)
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
