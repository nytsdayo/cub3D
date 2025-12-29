/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

const char	*get_error_message(t_error_code code);
void		cleanup_resources(t_cleanup_data *cleanup_data);

static void	print_error_header(void)
{
	write(2, "Error\n", 6);
}

static void	print_error_msg(const char *msg, const char *context)
{
	write(2, msg, ft_strlen(msg));
	if (context)
	{
		write(2, ": ", 2);
		write(2, context, ft_strlen(context));
	}
	write(2, "\n", 1);
}

void	error_exit(t_error_code code, const char *ctx, void *cleanup)
{
	const char	*msg;

	print_error_header();
	msg = get_error_message(code);
	print_error_msg(msg, ctx);
	if (cleanup)
		cleanup_resources((t_cleanup_data *)cleanup);
	exit(1);
}

void	error_exit_simple(t_error_code error_code)
{
	error_exit(error_code, NULL, NULL);
}
