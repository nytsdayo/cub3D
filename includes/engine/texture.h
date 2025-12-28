/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/19 00:00:00 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "cub3d.h"
#include "parse/parse.h"
#include "raycasting.h"

/* Texture Loading */
void init_textures(t_game *game, t_config_data *config);
void load_texture(t_game *game, t_img *texture, char *path);
void init_colors(t_game *game, t_config_data *config);

/* Texture Sampling */
int get_texture_pixel(t_img *texture, int x, int y);
t_img *select_wall_texture(t_game *game, t_ray *ray);

/* Texture Cleanup */
void cleanup_textures(t_game *game);

#endif
