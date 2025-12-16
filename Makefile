# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/18 00:00:00 by rnakatan          #+#    #+#              #
#    Updated: 2025/11/24 11:11:27 by rnakatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./includes/parse -I./includes/engine -I./includes/utils

# OS Detection
UNAME_S := $(shell uname -s)

# Directories
SRC_DIR = srcs
OBJ_DIR = obj
LIB_DIR = libraries

# Source files
SRCS = $(SRC_DIR)/main.c \
	   $(SRC_DIR)/parse/parse.c \
	   $(SRC_DIR)/parse/config/parse_config.c \
	   $(SRC_DIR)/parse/config/load_config.c \
	   $(SRC_DIR)/parse/map/parse_map.c \
	   $(SRC_DIR)/utils/ft_strlen.c \
	   $(SRC_DIR)/utils/ft_strcmp.c \
	   $(SRC_DIR)/utils/ft_strndup.c \
	   $(SRC_DIR)/utils/ft_isdigit.c \
	   $(SRC_DIR)/utils/ft_isspace.c \
	   $(SRC_DIR)/utils/read_map.c \
	   $(SRC_DIR)/utils/free_map.c \
	   $(SRC_DIR)/engine/init/init_game.c \
	   $(SRC_DIR)/engine/game_loop.c \
	   $(SRC_DIR)/engine/renderer/render_frame.c \
	   $(SRC_DIR)/engine/raycasting/mock_world.c \
	   $(SRC_DIR)/engine/raycasting/raycasting.c \
	   $(SRC_DIR)/engine/raycasting/ray_init.c \
	   $(SRC_DIR)/engine/raycasting/ray_dda.c \
	   $(SRC_DIR)/engine/raycasting/ray_draw.c \
	   $(SRC_DIR)/utils/cleanup.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# MLX Configuration
ifeq ($(UNAME_S), Linux)
	MLX_PATH = $(LIB_DIR)/minilibx-linux
	MLX_NAME = minilibx-linux.tgz
	MLX_LIB = $(MLX_PATH)/libmlx.a
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
	INCLUDES += -I$(MLX_PATH)
else
	MLX_PATH = $(LIB_DIR)/minilibx_opengl_20191021
	MLX_NAME = minilibx_macos_opengl.tgz
	MLX_LIB = $(MLX_PATH)/libmlx.a
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit -lm
	INCLUDES += -I$(MLX_PATH)
endif

# Rules
all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "Extracting MLX..."
	@tar -xzf $(LIB_DIR)/$(MLX_NAME) -C $(LIB_DIR)
	@echo "Compiling MLX..."
	@make -C $(MLX_PATH) 2>/dev/null || true

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@if [ -d "$(MLX_PATH)" ]; then make -C $(MLX_PATH) clean; fi

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_PATH)

re: fclean all

# Test target for parse_map module
TEST_MAP_NAME = test_parse_map
TEST_MAP_SRCS = $(SRC_DIR)/parse/map/test_parse_map.c \
				$(SRC_DIR)/parse/map/parse_map.c \
				$(SRC_DIR)/utils/ft_strlen.c \
				$(SRC_DIR)/utils/ft_strndup.c \
				$(SRC_DIR)/utils/read_map.c \
				$(SRC_DIR)/utils/free_map.c
TEST_MAP_OBJS = $(TEST_MAP_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

test_parse_map: $(TEST_MAP_OBJS)
	$(CC) $(CFLAGS) $(TEST_MAP_OBJS) -o $(TEST_MAP_NAME)
	./$(TEST_MAP_NAME)

.PHONY: all clean fclean re test_parse_map
