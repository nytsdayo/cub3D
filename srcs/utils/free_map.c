/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 08:17:34 by rnakatan          #+#    #+#             */
/*   Updated: 2025/11/24 08:17:53 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void free_map(void **map) {
  size_t i;

  if (map == NULL)
    return;
  i = 0;
  while (map[i] != NULL) {
    free(map[i]);
    i++;
  }
  free(map);
}
