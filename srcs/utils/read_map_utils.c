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
#include "error_manage.h"

char	*duplicate_line(const char *start, const char *end)
{
	size_t	len;
	char	*dup;

	len = end - start;
	if (len > 0 && start[len - 1] == '\r')
		len--;
	dup = malloc(len + 1);
	if (!dup)
		return (set_error_status(ERR_MALLOC_FAILURE), NULL);
	if (len > 0)
		ft_memcpy(dup, start, len);
	dup[len] = '\0';
	return (dup);
}

char	*resize_buffer(char *old, int old_size, int new_size)
{
	char	*new;
	int		i;

	new = malloc(new_size);
	if (!new)
		return (set_error_status(ERR_MALLOC_FAILURE), free(old), NULL);
	i = 0;
	while (i < old_size)
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	return (new);
}

char	**resize_map(char **old, int old_size, int new_size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * new_size);
	if (!new)
		return (set_error_status(ERR_MALLOC_FAILURE), free_map((void **)old), NULL);
	i = 0;
	while (i < old_size)
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	return (new);
}

const char	*process_line(char ***map, int *lines,
				const char *start, const char *end)
{
	*map = resize_map(*map, *lines, *lines + 2);
	if (!*map)
		return (NULL);
	if (get_error_status() != 0)
		return (NULL);
	(*map)[*lines] = duplicate_line(start, end);
	if (get_error_status() != 0)
		return (free_map((void **)*map), *map = NULL, NULL);
	if (!(*map)[(*lines)++])
		return (free_map((void **)*map), *map = NULL, NULL);
	if (*end == '\n')
		return (end + 1);
	return (end);
}
