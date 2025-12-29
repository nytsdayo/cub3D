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
 * @brief Error code enumeration
 */
typedef enum e_error_code
{
	ERR_INVALID_ARGC = 100,
	ERR_INVALID_ARGV,
	ERR_UNKNOWN_IDENTIFIER = 200,
	ERR_DUPLICATE_IDENTIFIER,
	ERR_SYNTAX_TEXTURE,
	ERR_SYNTAX_RGB,
	ERR_MISSING_IDENTIFIER,
	ERR_CONFIG_AFTER_MAP,
	ERR_MINIMUM_MAP_SIZE = 300,
	ERR_MAXIMUM_MAP_SIZE,
	ERR_WALL_ENCLOSURE,
	ERR_PLAYER_COUNT_ZERO,
	ERR_PLAYER_COUNT_MULTIPLE,
	ERR_ROW_LENGTH_INCONSISTENT,
	ERR_INVALID_CHARACTER,
	ERR_SPACE_VOID_CONTACT,
	ERR_FILE_NOT_FOUND = 400,
	ERR_FILE_READ_PERMISSION,
	ERR_INVALID_FILE_EXTENSION,
	ERR_INVALID_PATH,
	ERR_MALLOC_FAILURE = 500,
	ERR_BUFFER_OVERFLOW,
	ERR_MLX_INIT_FAILURE = 600,
	ERR_WINDOW_CREATION_FAILURE,
	ERR_IMAGE_CREATION_FAILURE,
	ERR_TEXTURE_LOAD_FAILURE,
	ERR_DDA_OUT_OF_BOUNDS = 700,
	ERR_DRAW_COORD_OUT_OF_RANGE,
	ERR_GENERIC = 900,
}	t_error_code;

/**
 * @brief Warning code enumeration
 */
typedef enum e_warning_code
{
	WARN_UNREACHABLE_AREA = 1,
	WARN_PERFORMANCE_ISSUE,
}	t_warning_code;

/**
 * @brief Cleanup data structure
 */
typedef struct s_cleanup_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	**map;
	void	*config;
	int		mlx_initialized;
	int		window_created;
}	t_cleanup_data;

/**
 * @brief Output a simple error message to stderr
 * @param msg The error message to output
 * @return Always returns -1 for convenient error handling
 */
int		error_msg(const char *msg);

/**
 * @brief Unified error handler with cleanup
 * @param error_code Error code enumeration
 * @param context Optional context information
 * @param cleanup_data Cleanup data structure pointer
 */
void	error_exit(t_error_code code, const char *ctx, void *cleanup);

/**
 * @brief Simple error exit without cleanup
 * @param error_code Error code enumeration
 */
void	error_exit_simple(t_error_code error_code);

/**
 * @brief Display warning message (program continues)
 * @param warning_code Warning code enumeration
 * @param context Optional context information
 */
void	error_warning(t_warning_code warning_code, const char *context);

#endif
