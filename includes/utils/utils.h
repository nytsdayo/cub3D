/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:25:29 by rnakatan          #+#    #+#             */
/*   Updated: 2025/11/24 10:51:24 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include "cub3d.h"
#include <stddef.h>

size_t ft_strlen(const char *s);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strndup(const char *s, size_t len);
const char **read_map(const char *filename);
void free_map(void **map);

/* Cleanup */
int close_window(t_game *game);
void cleanup_game(t_game *game);
int handle_keypress(int keycode, t_game *game);

#endif