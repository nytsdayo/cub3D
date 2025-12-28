/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkawano <mkawano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:29:19 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/28 20:29:22 by mkawano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*duplicate_line(const char *start, const char *end)
{
	size_t	len;
	char	*dup;

	len = end - start;
	if (len > 0 && start[len - 1] == '\r')
		len--;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	if (len > 0)
		ft_memcpy(dup, start, len);
	dup[len] = '\0';
	return (dup);
}
