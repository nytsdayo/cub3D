/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_warning.c                                    :+:      :+:    :+:   */
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

static const char	*get_warning_message(t_warning_code code)
{
	if (code == WARN_UNREACHABLE_AREA)
		return ("Unreachable area detected");
	if (code == WARN_PERFORMANCE_ISSUE)
		return ("Performance issue detected");
	return ("Warning");
}

void	error_warning(t_warning_code warning_code, const char *context)
{
	const char	*msg;

	write(2, "Warning: ", 9);
	msg = get_warning_message(warning_code);
	write(2, msg, ft_strlen(msg));
	if (context)
	{
		write(2, ": ", 2);
		write(2, context, ft_strlen(context));
	}
	write(2, "\n", 1);
}
