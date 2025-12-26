/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:25:29 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/25 19:53:38 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include "cub3d.h"
#include <stddef.h>

size_t ft_strlen(const char *s);
int ft_strcmp(const char *s1, const char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strndup(const char *s, size_t len);
int ft_isspace(int c);
int ft_isdigit(int c);
int is_blank_line(const char *line);
const char **read_map(const char *filename);
void free_map(void **map);

/* Cleanup */
void cleanup_game(t_game *game);

#endif
