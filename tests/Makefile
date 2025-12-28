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

# Directories
ROOT_DIR = ..
SRC_DIR = $(ROOT_DIR)/srcs
TEST_DIR = .

# Compiler and flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++11
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(ROOT_DIR)/includes -I$(ROOT_DIR)/includes/parse -I$(ROOT_DIR)/includes/utils -I$(ROOT_DIR)/libraries/minilibx-linux -I./

# Test executables
TEST_PARSE_CONFIG = test_parse_config
TEST_PARSE_MAP = test_parse_map
UNIT_TESTS = $(TEST_PARSE_CONFIG) $(TEST_PARSE_MAP)

# Binary under test
CUB3D_BIN = $(ROOT_DIR)/cub3D
PARSER_BIN = $(abspath $(TEST_DIR)/parser_cli)

# C++ test source
PARSE_CONFIG_CPP = $(TEST_DIR)/parse/config/test_parse_config.cpp \
				   $(TEST_DIR)/test_utils.cpp

# C source files (library code)
PARSE_CONFIG_C_SRCS = $(SRC_DIR)/parse/config/parse_config.c \
					  $(SRC_DIR)/parse/config/detect_identifier.c \
					  $(SRC_DIR)/parse/config/validate_format.c \
					  $(SRC_DIR)/parse/config/load_config_utils.c \
					  $(SRC_DIR)/utils/ft_strlen.c \
					  $(SRC_DIR)/utils/ft_strcmp.c \
					  $(SRC_DIR)/utils/ft_strncmp.c \
					  $(SRC_DIR)/utils/ft_strndup.c \
					  $(SRC_DIR)/utils/ft_memcpy.c \
					  $(SRC_DIR)/utils/ft_isspace.c \
					  $(SRC_DIR)/utils/ft_isdigit.c \
					  $(SRC_DIR)/utils/is_blank_line.c \
					  $(SRC_DIR)/utils/read_map.c \
					  $(SRC_DIR)/utils/free_map.c \
					  $(SRC_DIR)/utils/error_msg.c

TEST_MAP_CXX_SRCS = $(TEST_DIR)/parse/map/test_parse_map.cpp \
					$(TEST_DIR)/parse/map/test_map_file.cpp
TEST_MAP_C_SRCS = $(SRC_DIR)/parse/map/parse_map.c \
				  $(SRC_DIR)/parse/map/load_map.c \
				  $(SRC_DIR)/parse/map/parse_map_utils.c \
				  $(SRC_DIR)/parse/map/parse_map_validate.c \
				  $(SRC_DIR)/parse/map/parse_map_walls.c \
				  $(SRC_DIR)/parse/map/parse_map_spaces.c \
				  $(SRC_DIR)/utils/ft_strlen.c \
				  $(SRC_DIR)/utils/ft_strndup.c \
				  $(SRC_DIR)/utils/ft_memcpy.c \
				  $(SRC_DIR)/utils/is_blank_line.c \
				  $(SRC_DIR)/utils/ft_isspace.c \
				  $(SRC_DIR)/utils/read_map.c \
				  $(SRC_DIR)/utils/free_map.c \
				  $(SRC_DIR)/utils/error_msg.c

PARSER_SRCS = $(SRC_DIR)/parse/parse.c \
			  $(SRC_DIR)/parse/load_data.c \
			  $(SRC_DIR)/parse/config/parse_config.c \
			  $(SRC_DIR)/parse/config/detect_identifier.c \
			  $(SRC_DIR)/parse/config/validate_format.c \
			  $(SRC_DIR)/parse/config/load_config.c \
			  $(SRC_DIR)/parse/config/load_config_utils.c \
			  $(SRC_DIR)/parse/map/parse_map.c \
			  $(SRC_DIR)/parse/map/parse_map_utils.c \
			  $(SRC_DIR)/parse/map/parse_map_validate.c \
			  $(SRC_DIR)/parse/map/parse_map_walls.c \
			  $(SRC_DIR)/parse/map/parse_map_spaces.c \
			  $(SRC_DIR)/parse/map/load_map.c \
			  $(SRC_DIR)/utils/ft_strlen.c \
			  $(SRC_DIR)/utils/ft_strcmp.c \
			  $(SRC_DIR)/utils/ft_strncmp.c \
			  $(SRC_DIR)/utils/ft_strndup.c \
			  $(SRC_DIR)/utils/ft_memcpy.c \
			  $(SRC_DIR)/utils/ft_isspace.c \
			  $(SRC_DIR)/utils/ft_isdigit.c \
			  $(SRC_DIR)/utils/is_blank_line.c \
			  $(SRC_DIR)/utils/read_map.c \
			  $(SRC_DIR)/utils/free_map.c \
			  $(SRC_DIR)/utils/free_config_data.c \
			  $(SRC_DIR)/utils/error_msg.c \
			  $(TEST_DIR)/parser_cli.c

# Object files
PARSE_CONFIG_CPP_OBJ = $(PARSE_CONFIG_CPP:.cpp=.o)
PARSE_CONFIG_C_OBJS = $(PARSE_CONFIG_C_SRCS:.c=.o)
TEST_MAP_CXX_OBJS = $(TEST_MAP_CXX_SRCS:.cpp=.o)
TEST_MAP_C_OBJS = $(TEST_MAP_C_SRCS:.c=.o)
TEST_MAP_OBJS = $(TEST_MAP_CXX_OBJS) $(TEST_MAP_C_OBJS)
UNIT_OBJS = $(PARSE_CONFIG_CPP_OBJ) $(PARSE_CONFIG_C_OBJS) $(TEST_MAP_OBJS)
PARSER_OBJS = $(PARSER_SRCS:.c=.o)

# Rules
all: test

test: unit
	$(MAKE) build
	$(MAKE) parser-tests
	$(MAKE) leak-check

unit: $(UNIT_TESTS)
	./$(TEST_PARSE_CONFIG)
	./$(TEST_PARSE_MAP)

parser-tests:
	$(MAKE) $(PARSER_BIN)
	@chmod +x ./run_parser_tests.sh
	PARSER_BIN="$(PARSER_BIN)" ./run_parser_tests.sh

leak-check:
	@if [ ! -x "$(CUB3D_BIN)" ]; then $(MAKE) -C $(ROOT_DIR); fi
	@chmod +x ./run_leak_check.sh
	./run_leak_check.sh

build:
	$(MAKE) -C $(ROOT_DIR)

$(TEST_PARSE_CONFIG): $(PARSE_CONFIG_CPP_OBJ) $(PARSE_CONFIG_C_OBJS)
	$(CXX) $(CXXFLAGS) $(PARSE_CONFIG_CPP_OBJ) $(PARSE_CONFIG_C_OBJS) -o $(TEST_PARSE_CONFIG)

$(TEST_PARSE_MAP): $(TEST_MAP_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_MAP_OBJS) -o $(TEST_PARSE_MAP)

$(PARSER_BIN): $(PARSER_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(PARSER_OBJS) -o $(PARSER_BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(UNIT_OBJS) $(PARSER_OBJS)

fclean: clean
	rm -f $(UNIT_TESTS) $(PARSER_BIN)

re: fclean all

.PHONY: all clean fclean re test unit parser-tests leak-check build
