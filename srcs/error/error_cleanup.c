/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manage.h"
#include "utils.h"
#include <stdlib.h>

void	cleanup_resources(t_cleanup_data *cleanup_data)
{
	if (!cleanup_data)
		return ;
	if (cleanup_data->config)
		free_config_data(cleanup_data->config);
	if (cleanup_data->map)
		free_map((void **)cleanup_data->map);
	free(cleanup_data);
}
