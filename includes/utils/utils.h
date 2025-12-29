/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:25:29 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 22:58:10 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"
# include "parse.h"
# include "error_manage.h"
# include <stddef.h>

size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(const char *s, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_isspace(int c);
int			ft_isdigit(int c);
int			is_blank_line(const char *line);
const char	**read_map(const char *filename);
void		free_map(void **map);
char		*resize_buffer(char *old, int old_size, int new_size);

/* Cleanup */
void		cleanup_game(t_game *game);
void		free_config_data(t_config_data *config);

#endif
