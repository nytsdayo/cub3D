/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:18:08 by rnakatan          #+#    #+#             */
/*   Updated: 2025/11/24 10:51:35 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "parse.h"

static int	valid_args(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	const char	**map;

	if (valid_args(argc, argv) != 0)
		return (EXIT_FAILURE);
	map = read_map(argv[1]);
	if (map == NULL)
	{
		write(0, "Error\n", 6);
		return (EXIT_FAILURE);
	}
	if (parse(map) != 0)
		return (EXIT_FAILURE);
	free_map((void **)map);
	return (EXIT_SUCCESS);
}

static int	valid_args(int argc, char *argv[])
{
	if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0)
	{
		write(0, "Error\n", 6);
		return (1);
	}
	return (0);
}
