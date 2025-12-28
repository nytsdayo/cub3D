/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void free_config_data(t_config_data *config) {
  free(config->north_texture_path);
  free(config->south_texture_path);
  free(config->west_texture_path);
  free(config->east_texture_path);
}
