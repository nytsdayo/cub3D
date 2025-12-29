/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 22:54:33 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 22:56:42 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

static int	skip_to_value_start(const char *line, t_identifier id);

char	*extract_texture_path(const char *line, t_identifier id)
{
	int		i;
	int		start;
	int		len;

	i = skip_to_value_start(line, id);
	start = i;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '\n')
		i++;
	len = i - start;
	return (ft_strndup(&line[start], len));
}

static int	skip_to_value_start(const char *line, t_identifier id)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (id >= ID_NO && id <= ID_EA)
		i += 2;
	else
		i += 1;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}
