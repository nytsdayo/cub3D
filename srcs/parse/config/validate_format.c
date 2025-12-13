/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

/**
 * @brief RGB値の1つの成分を解析する
 */
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

/**
 * @brief テクスチャパスのフォーマットを検証する（.xpm拡張子チェック）
 */
int	validate_texture_format(const char *line, t_identifier id)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
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
	if (len < 5)
		return (-1);
	if (line[start + len - 4] != '.' || line[start + len - 3] != 'x'
		|| line[start + len - 2] != 'p' || line[start + len - 1] != 'm')
		return (-1);
	return (0);
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
	i++;
	while (ft_isspace(line[i]))
		i++;
	if (parse_rgb_component(line, &i) == -1 || line[i++] != ','
		|| parse_rgb_component(line, &i) == -1 || line[i++] != ','
		|| parse_rgb_component(line, &i) == -1)
		return (-1);
	return (0);
}
