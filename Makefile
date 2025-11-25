# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/18 00:00:00 by cub3d             #+#    #+#              #
#    Updated: 2025/11/24 11:11:27 by rnakatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./includes/parse -I./includes/engine -I./includes/utils

# Directories
SRC_DIR = srcs
OBJ_DIR = obj
BONUS_DIR = bonus

# Source files
SRCS = $(SRC_DIR)/main.c \
	   $(SRC_DIR)/parse/parse.c \
	   $(SRC_DIR)/utils/ft_strlen.c \
	   $(SRC_DIR)/utils/ft_strcmp.c \
	   $(SRC_DIR)/utils/ft_strndup.c \
	   $(SRC_DIR)/utils/read_map.c \
	   $(SRC_DIR)/utils/free_map.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
