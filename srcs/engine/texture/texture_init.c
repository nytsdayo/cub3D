/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/19 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "texture.h"
#include "utils.h"

void	load_texture(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures.width, &game->textures.height);
	if (!texture->img)
	{
		error_msg("Error\nTexture loading failed\n");
		exit(EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length,
			&texture->endian);
}

void	init_textures(t_game *game, t_config_data *config)
{
	game->textures.width = TEX_WIDTH;
	game->textures.height = TEX_HEIGHT;
	load_texture(game, &game->textures.north, config->north_texture_path);
	load_texture(game, &game->textures.south, config->south_texture_path);
	load_texture(game, &game->textures.east, config->east_texture_path);
	load_texture(game, &game->textures.west, config->west_texture_path);
}

void	init_colors(t_game *game, t_config_data *config)
{
	game->ceiling_color.r = config->ceiling_color.r;
	game->ceiling_color.g = config->ceiling_color.g;
	game->ceiling_color.b = config->ceiling_color.b;
	game->floor_color.r = config->floor_color.r;
	game->floor_color.g = config->floor_color.g;
	game->floor_color.b = config->floor_color.b;
}
