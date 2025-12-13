# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#              #
#    Updated: 2025/12/13 00:00:00 by rnakatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Test executables
TEST_PARSE_CONFIG = test_parse_config

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I../includes -I../includes/parse -I../includes/utils -I../libraries/minilibx-linux

# Directories
SRC_DIR = ../srcs
TEST_DIR = .

# Source files for parse_config test
PARSE_CONFIG_SRCS = $(TEST_DIR)/parse/config/test_parse_config.c \
					$(SRC_DIR)/parse/config/parse_config.c \
					$(SRC_DIR)/utils/ft_strlen.c \
					$(SRC_DIR)/utils/ft_strcmp.c \
					$(SRC_DIR)/utils/ft_strncmp.c \
					$(SRC_DIR)/utils/ft_strndup.c \
					$(SRC_DIR)/utils/ft_isspace.c \
					$(SRC_DIR)/utils/ft_isdigit.c \
					$(SRC_DIR)/utils/is_blank_line.c \
					$(SRC_DIR)/utils/read_map.c \
					$(SRC_DIR)/utils/free_map.c

# Object files
PARSE_CONFIG_OBJS = $(PARSE_CONFIG_SRCS:.c=.o)

# Rules
all: $(TEST_PARSE_CONFIG)

$(TEST_PARSE_CONFIG): $(PARSE_CONFIG_OBJS)
	$(CC) $(CFLAGS) $(PARSE_CONFIG_OBJS) -o $(TEST_PARSE_CONFIG)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(PARSE_CONFIG_OBJS)

fclean: clean
	rm -f $(TEST_PARSE_CONFIG)

re: fclean all

.PHONY: all clean fclean re
