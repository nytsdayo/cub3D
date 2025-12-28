/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@github.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2025/12/28 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

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

/**
 * @brief Output a formatted error message to stderr using fprintf
 * @param format The format string (printf-style)
 * @param ... Variable arguments for the format string
 * @return Always returns -1 for convenient error handling
 */
int	error_msg_format(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	return (-1);
}
