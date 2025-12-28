/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/**
 * @brief Output a simple error message to stderr
 * @param msg The error message to output
 * @return Always returns -1 for convenient error handling
 */
int	error_msg(const char *msg);

/**
 * @brief Output a formatted error message to stderr using fprintf
 * @param format The format string (printf-style)
 * @param ... Variable arguments for the format string
 * @return Always returns -1 for convenient error handling
 */
int	error_msg_format(const char *format, ...);

#endif
