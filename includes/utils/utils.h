/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:25:29 by rnakatan          #+#    #+#             */
/*   Updated: 2025/11/24 08:32:13 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stddef.h>

size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
const char	**read_map(const char *filename);
void		free_map(void **map);


#endif // UTILS_H