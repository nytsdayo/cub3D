/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 01:21:58 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/20 01:28:16 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

t_identifier detect_identifier(const char *line) {
  int i;

  i = 0;
  while (ft_isspace(line[i]))
    i++;
  if (ft_strncmp(&line[i], "NO", 2) == 0 && ft_isspace(line[i + 2]))
    return (ID_NO);
  if (ft_strncmp(&line[i], "SO", 2) == 0 && ft_isspace(line[i + 2]))
    return (ID_SO);
  if (ft_strncmp(&line[i], "WE", 2) == 0 && ft_isspace(line[i + 2]))
    return (ID_WE);
  if (ft_strncmp(&line[i], "EA", 2) == 0 && ft_isspace(line[i + 2]))
    return (ID_EA);
  if (line[i] == 'F' && line[i + 1] && ft_isspace(line[i + 1]))
    return (ID_F);
  if (line[i] == 'C' && line[i + 1] && ft_isspace(line[i + 1]))
    return (ID_C);
  return (ID_UNKNOWN);
}
