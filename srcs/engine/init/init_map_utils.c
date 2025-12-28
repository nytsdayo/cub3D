/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/28 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_dimensions(char **map, int *width, int *height)
{
	int	h;
	int	w;
	int	max_w;

	h = 0;
	max_w = 0;
	while (map[h])
	{
		w = 0;
		while (map[h][w])
			w++;
		if (w > max_w)
			max_w = w;
		h++;
	}
	*width = max_w;
	*height = h;
}

int	**allocate_world_map(int width, int height)
{
	int	**world_map;
	int	i;

	world_map = malloc(sizeof(int *) * height);
	if (!world_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		world_map[i] = malloc(sizeof(int) * width);
		if (!world_map[i])
		{
			while (i > 0)
				free(world_map[--i]);
			free(world_map);
			return (NULL);
		}
		i++;
	}
	return (world_map);
}
