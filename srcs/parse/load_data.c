/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 01:06:30 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/27 00:45:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdlib.h>

int	load_data(const char **input_data, void *data)
{
	t_game_data		*game_data;
	size_t			line_index;
	size_t			id_count;
	t_identifier		id;

	game_data = (t_game_data *)data;
	if (load_config(input_data, &game_data->config) != 0)
		return (-1);
	line_index = 0;
	id_count = 0;
	while (input_data[line_index])
	{
		if (is_blank_line(input_data[line_index]))
		{
			line_index++;
			continue ;
		}
		id = detect_identifier(input_data[line_index]);
		if (id != ID_UNKNOWN)
		{
			if (id_count >= 6)
				return (write(2, "Error\n", 6), -1);
			id_count++;
			line_index++;
			continue ;
		}
		if (id_count < 6)
			return (write(2, "Error\n", 6), -1);
		break ;
	}
	if (id_count < 6)
		return (write(2, "Error\n", 6), -1);
	if (load_map((char **)input_data, line_index, &game_data->map) != 0)
		return (-1);
	return (0);
}
