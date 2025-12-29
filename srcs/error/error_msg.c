/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manage.h"
#include "utils.h"
#include <unistd.h>

/**
 * @brief Output a simple error message to stderr
 * @param msg The error message to output
 * @return Always returns -1 for convenient error handling
 */
int	error_msg(const char *msg)
{
	size_t	len;

	len = ft_strlen(msg);
	write(2, msg, len);
	return (-1);
}
