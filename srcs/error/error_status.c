/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manage.h"

static t_error_code g_error_status = 0;

void set_error_status(t_error_code error_code) { g_error_status = error_code; }

t_error_code get_error_status(void) { return (g_error_status); }

void clear_error_status(void) { g_error_status = 0; }
